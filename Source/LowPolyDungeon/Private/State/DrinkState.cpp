// Fill out your copyright notice in the Description page of Project Settings.


#include "State/DrinkState.h"
#include "Actor/LowPolyCharacter.h"
#include "Component/StatComponent.h"

UDrinkState::UDrinkState()
{

}

void UDrinkState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Drink Init!!"));
}

void UDrinkState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		if (key == EKeys::SpaceBar)
		{
			FSMRef->PushState(ECharacterState::ECS_Dodge);
		}
		break;
	case IE_Released:
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

void UDrinkState::Enter_Implementation(float animationplayRate)
{
//	Super::Enter_Implementation(animationplayRate);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Drink Enter!!"));
}

void UDrinkState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	OwnedPlayer->StatComponent->RegenerateHealth(20.0f * DeltaTime);
}

void UDrinkState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Drink Exit!!"));
}

float UDrinkState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}
