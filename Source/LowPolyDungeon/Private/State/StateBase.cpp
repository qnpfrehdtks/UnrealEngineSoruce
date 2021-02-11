// Fill out your copyright notice in the Description page of Project Settings.


#include "State/StateBase.h"
#include "Engine/Engine.h"
#include "Actor/LowpolyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Component/FSMComponent.h"
#include "Component/TargetingComponent.h"

UStateBase::UStateBase()
{
	//StateName = TEXT(" ");
	EState = ECharacterState::ECS_None;
	bIsTargetCamera = true;
	bIsTargetRotation = true;
	playRate = 1.0f;
	blockRate = 1.0f;
	sectionName = NAME_None;


}

void UStateBase::Init_Implementation(const FStateData& newData)
{

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %s Init"), *(StaticClass()->GetFName().ToString())));
	elapsedTime = 0.0f;
	FSMRef = OwnedPlayer->FSM;

	//if (newData != nullptr)
	{
		EState = newData.CharacterState;
		animMontage = newData.anim;
		bCanMove = newData.bCanMove;
		bIsTargetCamera = newData.bIsTargetCamera;
		bIsTargetRotation = newData.bIsTargetRotation;
		consumeStamina = newData.consumeStamina;
		plusStaminaPerSecond = newData.plusStaminaPerSec;
		playRate = newData.playRate;
		sectionName = newData.sectionName;
		attackType = newData.attackType;
		attackArmor = newData.attackArmor;
		blockRate = newData.blockRate;
	}

	//NextReservedState = nullptr;
}

void UStateBase::Enter_Implementation(float animationplayRate)
{

	
	//NextReservedState = nullptr;
	elapsedTime = 0.0f;
	EnterDelegate.Broadcast();
	
	OwnedPlayer->consumeStamina(consumeStamina);

	if (animMontage)
	{
		OwnedPlayer->PlayAnimMontage(animMontage, playRate * animationplayRate, sectionName);
	}
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %s Enter"), *(StaticClass()->GetFName().ToString())));
}



void UStateBase::Update_Implementation(float DeltaTime)
{
	elapsedTime += DeltaTime;
	UpdateDelegate.Broadcast(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %s Update"), *(StaticClass()->GetFName().ToString())));
}

float UStateBase::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	if (attackArmor == ECharacterHitArmor::ECH_AllImmune)
	{
		return DMG;
	}

	switch (dmgType)
	{
		case EAttackType::EAT_NoStun:
			break;
		case EAttackType::EAT_LightStun:
			if (attackArmor == ECharacterHitArmor::EAT_LightImmume || attackArmor == ECharacterHitArmor::EAT_StrongImmume)
			{
				return DMG;
			}
			FSMRef->ChangeState(ECharacterState::ECS_LightStun);
			break;
		case EAttackType::EAT_StrongStun:
			if (attackArmor == ECharacterHitArmor::EAT_StrongImmume)
			{
				return DMG;
			}
			FSMRef->ChangeState(ECharacterState::ECS_StrongStun);
			break;
		case EAttackType::EAT_KnockDown:
			FSMRef->ChangeState(ECharacterState::ECS_KnockDown);
			break;
		default:
		break;
	}

	return DMG;
}

void UStateBase::Exit_Implementation()
{
	//NextReservedState = nullptr;
	elapsedTime = 0;
	EndDelegate.Broadcast();

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %s exit"), *(StaticClass()->GetFName().ToString())));
}

void UStateBase::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %s HanldeInput"), *(StaticClass()->GetFName().ToString())));
}


