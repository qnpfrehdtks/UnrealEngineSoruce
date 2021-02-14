// Fill out your copyright notice in the Description page of Project Settings.


#include "State/IdleState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UIdleState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Idle Init!!"));


}

void UIdleState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		if (key == EKeys::R)
		{
			FSMRef->ChangeState(ECharacterState::ECS_EquipChange);
		}
		if (key == EKeys::E)
		{
			OwnedPlayer->UseSelectedItem(0);
		}
		if (key == EKeys::RightMouseButton)
		{
			FSMRef->ChangeState(ECharacterState::ECS_Block);
		}
		if (key == EKeys::LeftMouseButton)
		{
			FSMRef->ChangeState(ECharacterState::ECS_Attack1);
		}
		if (key == EKeys::SpaceBar)
		{
			FSMRef->ChangeState(ECharacterState::ECS_Dodge);
		}
		break;
	case IE_Released:
		break;
	case IE_Repeat:
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

UIdleState::UIdleState()
{

}

void UIdleState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Idle Enter!!"));
}

void UIdleState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	if (OwnedPlayer != nullptr)
	{
		if (OwnedPlayer->GetVelocity().SizeSquared() > 0.5f )
		{
			FSMRef->ChangeState(ECharacterState::ECS_Walk);
		}
	}
}
void UIdleState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Idle End!!"));
}


float UIdleState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}

