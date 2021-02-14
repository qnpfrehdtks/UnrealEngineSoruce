#include "State/DeadState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDeadState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("Dead Init!!"));
}

void UDeadState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
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

UDeadState::UDeadState()
{

}

void UDeadState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("Stun Enter!!"));

	//FSMRef->AllClearState();
}

void UDeadState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

}
void UDeadState::Exit_Implementation()
{
	Super::Exit_Implementation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("Stun End!!"));
}

float UDeadState::Damaged(EAttackType dmgType, FVector dmgPosition, float DMG)
{
	return 0;
}
