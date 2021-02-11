// Fill out your copyright notice in the Description page of Project Settings.


#include "State/ChangeEquipState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UChangeEquipState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Equip Init!!"));


}

void UChangeEquipState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
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

UChangeEquipState::UChangeEquipState()
{

}

void UChangeEquipState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Equip Enter!!"));
}

void UChangeEquipState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);
}
void UChangeEquipState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Equip End!!"));
}

float UChangeEquipState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}