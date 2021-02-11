// Fill out your copyright notice in the Description page of Project Settings.


#include "State/KnockDownState.h"
#include "Kismet/KismetMathLibrary.h"

#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

void UKnockDownState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("K Init!!"));


}

void UKnockDownState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
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
		break;
	case IE_MAX:
		break;
	default:
		break;
	}


}

UKnockDownState::UKnockDownState()
{

}

void UKnockDownState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Idle Enter!!"));
}

void UKnockDownState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);
}
void UKnockDownState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Idle End!!"));
}

float UKnockDownState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}