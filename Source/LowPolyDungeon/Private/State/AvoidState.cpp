#include "State/AvoidState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/LowpolyCharacter.h"
void UAvoidState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Avoid Init!!"));

 //  LastMoveInput = OwnedPlayer->GetLastMovementInputVector();
}

void UAvoidState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
{
	Super::HandleInput_Implementation(Input, key, axisValue);

	switch (Input)
	{
	case IE_Pressed:
		if (key == EKeys::LeftMouseButton && elapsedTime > 0.4f)
		{
			//FSMRef->PopAndPushState(TEXT("DashAttack"), true);
			elapsedTime = 0.0f;
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

UAvoidState::UAvoidState()
{

}

void UAvoidState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
	//OwnedPlayer->GetCharacterMovement()->bOrientRotationToMovement = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Avoid Enter!!"));
}

void UAvoidState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	/*if (OwnedPlayer == nullptr) return;
	
	if (LastMoveInput.IsZero() == false)
	{
		FVector lastVector = LastMoveInput.GetSafeNormal();
		OwnedPlayer->SetActorLocation(OwnedPlayer->GetActorLocation() + (lastVector * 100.0f * DeltaTime), true);
		FRotator targetRot = UKismetMathLibrary::MakeRotFromX(lastVector);

		FRotator resultRot = UKismetMathLibrary::RInterpTo(OwnedPlayer->GetActorRotation(), targetRot, DeltaTime, 5.0f);
		OwnedPlayer->SetActorRotation(resultRot);
	}*/
}
void UAvoidState::Exit_Implementation()
{
	Super::Exit_Implementation();
	//OwnedPlayer->GetCharacterMovement()->bOrientRotationToMovement = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Avoid End!!"));
}

float UAvoidState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return Super::Damaged(dmgType, dmgPosition, DMG);
}