// Fill out your copyright notice in the Description page of Project Settings.


#include "State/FallingState.h"
#include "Actor/LowpolyCharacter.h"
#include "Component/FSMComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/CharacterMovementComponent.h"

void UFallingState::Init_Implementation(const FStateData& newData)
{
	Super::Init_Implementation(newData);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Falling Init!!"));
}

void UFallingState::HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue)
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

UFallingState::UFallingState()
{

}

void UFallingState::Enter_Implementation(float animationplayRate)
{
	Super::Enter_Implementation(animationplayRate);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Falling Enter!!"));

	FSMRef->PopAllState();
}

void UFallingState::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	if (OwnedPlayer != nullptr)
	{
		if (OwnedPlayer->GetVelocity().Z <= 0.01f)
		{
			FSMRef->PlayTopState();
		}
	}
}
void UFallingState::Exit_Implementation()
{
	Super::Exit_Implementation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Falling End!!"));
}
