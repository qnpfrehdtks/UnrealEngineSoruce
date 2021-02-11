// Fill out your copyright notice in the Description page of Project Settings.


#include "State/SprintState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/CharacterMovementComponent.h"

void USprintState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Sprint Init!!"));
}

void USprintState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
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
		if (key == EKeys::LeftMouseButton && elapsedTime > 0.6f)
		{
			FSMRef->PushState(ECharacterState::ECS_DashAttack);
			elapsedTime = 0.0f;
		}
		if (key == EKeys::SpaceBar)
		{
			FSMRef->PushState(ECharacterState::ECS_Dodge);
		}
		if (key == EKeys::E)
		{
			OwnedPlayer->UseSelectedItem(0);
		}
		break;
	case IE_Released:
		if (key == EKeys::Q)
		{
			FSMRef->PushState(ECharacterState::ECS_Walk);
		}
		break;
	case IE_Repeat:
		break;
	case IE_DoubleClick:
		break;
	case IE_Axis:
	break;
	case IE_MAX:
		break;
	default:
		break;
	}


}

USprintState::USprintState()
{

}

void USprintState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Sprint Enter!!"));

	OwnedPlayer->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void USprintState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	if (OwnedPlayer != nullptr)
	{
		if (OwnedPlayer->GetVelocity().SizeSquared() <= 0.01f )
		{
			FSMRef->PopState();
		}
	}

}
void USprintState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Sprint End!!"));

	OwnedPlayer->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

float USprintState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}
