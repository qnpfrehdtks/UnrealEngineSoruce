// Fill out your copyright notice in the Description page of Project Settings.


#include "State/BlockingState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlockingState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Blocking Init!!"));

	bIsHoding = true;

}

void UBlockingState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		break;
	case IE_Released:
		if (key == EKeys::RightMouseButton)
		{
			bIsHoding = false;
		}
		break;
	case IE_Repeat:
		if (key == EKeys::RightMouseButton)
		{
			bIsHoding = true;
		}
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

UBlockingState::UBlockingState()
{

}

void UBlockingState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Blocking Enter!!"));
	bIsHoding = true;
}

void UBlockingState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);
}
void UBlockingState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Blocking End!!"));
}

float UBlockingState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	dmgPosition.Z = OwnedPlayer->GetActorLocation().Z;
	FVector attackDir = dmgPosition - OwnedPlayer->GetActorLocation();
	attackDir = attackDir.GetSafeNormal();

	//DrawDebugLine(GetWorld(), OwnedPlayer->GetActorLocation(), OwnedPlayer->GetActorLocation() + attackDir * 100.0f, FColor::Red, true, 5.0f);

	if (FVector::DotProduct(OwnedPlayer->GetActorForwardVector(), attackDir) < 0.6f)
	{
		return Super::Damaged(dmgType, dmgPosition, DMG);
	}

	float notBlockedDMG = DMG * (1.0f - blockRate);
	float blockedDMG = DMG * (blockRate);

	float currentStamina = OwnedPlayer->GetStamina();
	float resultConsumeStamina = notBlockedDMG;

	if (FSMRef->PushState_float(ECharacterState::ECS_Blocking, resultConsumeStamina) == false)
	{
		OwnedPlayer->consumeStamina(resultConsumeStamina);
		float resultDmg = DMG - currentStamina;
		return Super::Damaged(dmgType, dmgPosition, resultDmg);
	}

	OwnedPlayer->consumeStamina(resultConsumeStamina);

	return blockedDMG;
}
