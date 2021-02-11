// Fill out your copyright notice in the Description page of Project Settings.


#include "State/WalkState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

void UWalkState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Walk Init!!"));
}

void UWalkState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		if (key == EKeys::R)
		{
			FSMRef->PushState(ECharacterState::ECS_EquipChange);
			//FSMRef->PushState(ECharacterState::ECS_Drink);
		}
		if (key == EKeys::E)
		{
			OwnedPlayer->UseSelectedItem(0);
		}
		if (key == EKeys::RightMouseButton)
		{
			FSMRef->PushState(ECharacterState::ECS_Block);
		}
		if (key == EKeys::LeftMouseButton)
		{
			FSMRef->PushState(ECharacterState::ECS_Attack1);
		}
		if (key == EKeys::SpaceBar)
		{
			FSMRef->PushState(ECharacterState::ECS_Dodge);
			elapsedTime = 0.0f;
		}
		break;
	case IE_Released:
		break;
	case IE_Repeat:
		if (key == EKeys::Q && elapsedTime > 1.0f)
		{
			elapsedTime = 0.0f;
			FSMRef->PushState(ECharacterState::ECS_Sprint);
		}
		break;
	case IE_DoubleClick:
		break;
	case IE_Axis:
	{

	}
		break;
	case IE_MAX:
		break;
	default:
		break;
	}
}

UWalkState::UWalkState()
{

}

void UWalkState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Walk Enter!!"));
	OwnedPlayer->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void UWalkState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	if (OwnedPlayer != nullptr)
	{
		if (OwnedPlayer->GetVelocity().SizeSquared() <= 0.01f)
		{
			FSMRef->PopState();
		}
	}
}
void UWalkState::Exit_Implementation()
{
	Super::Exit_Implementation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Walk Exit!!"));
}

float UWalkState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}
