#include "State/BlockState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBlockState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Block Init!!"));
}

void UBlockState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		break;
	case IE_Released:
		if (key == EKeys::RightMouseButton )
		{
			FSMRef->ChangeState(ECharacterState::ECS_Idle);
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

UBlockState::UBlockState()
{

}

void UBlockState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Block Enter!!"));

	if (OwnedPlayer != nullptr)
	{
		OwnedPlayer->GetCharacterMovement()->bOrientRotationToMovement = false;
		OwnedPlayer->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
}

void UBlockState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

}
void UBlockState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Block End!!"));

	if (OwnedPlayer != nullptr)
	{
		OwnedPlayer->GetCharacterMovement()->bOrientRotationToMovement = true;
		//OwnedPlayer->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		OwnedPlayer->StopAnimMontage();
	}
}

float UBlockState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	dmgPosition.Z = OwnedPlayer->GetActorLocation().Z;
	FVector attackDir = dmgPosition - OwnedPlayer->GetActorLocation();
	attackDir = attackDir.GetSafeNormal();

	//DrawDebugLine(GetWorld(), OwnedPlayer->GetActorLocation(), OwnedPlayer->GetActorLocation() + attackDir * 100.0f, FColor::Red, true, 5.0f);

	if (FVector::DotProduct(OwnedPlayer->GetActorForwardVector(), attackDir) < 0.0f)
	{
		return Super::Damaged(dmgType, dmgPosition, DMG);
	}

	float notBlockedDMG = DMG * (1.0f - blockRate);
	float blockedDMG = DMG * (blockRate);

	float currentStamina = OwnedPlayer->GetStamina();
	float resultConsumeStamina = notBlockedDMG;

	

	if (FSMRef->ChangeState_float(ECharacterState::ECS_Blocking, resultConsumeStamina) == false)
	{
		OwnedPlayer->consumeStamina(resultConsumeStamina);
		float resultDmg = DMG - currentStamina;
		return Super::Damaged(dmgType, dmgPosition, resultDmg);
	}

	OwnedPlayer->consumeStamina(resultConsumeStamina);
	return blockedDMG;

}