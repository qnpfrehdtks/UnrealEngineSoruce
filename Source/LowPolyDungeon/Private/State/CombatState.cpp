// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CombatState.h"
#include "Component/FSMComponent.h"
#include "Actor/LowpolyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
void UCombatState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);

	attackMult = *(newData.Attribute.Find("attackMult"));
	attackCombo = *(newData.Attribute.Find("combo"));

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Attack%d Init!!"), attackCombo));
}

void UCombatState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		if (key == EKeys::LeftMouseButton )
		{
			FSMRef->ReserveState(ECharacterState::ECS_Attack2);
			FSMRef->bCanInput = false;
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

UCombatState::UCombatState()
{
	
}

void UCombatState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Attack Enter!!"));
	FSMRef->bCanInput = false;
 }
 
 void UCombatState::Update_Implementation(float DeltaTime)
 {
	 Super::Update_Implementation(DeltaTime);
 }
 void UCombatState::Exit_Implementation()
 {
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Attack Exit!!"));

	 Super::Exit_Implementation();
	 FSMRef->bCanInput = true;
	 OwnedPlayer->bIsinvincibility = false;
 }

 float UCombatState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
 {
	 return Super::Damaged(dmgType, dmgPosition, DMG);
 }
