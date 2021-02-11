// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/FSMComponent.h"
#include "Component/TargetingComponent.h"

#include "State/StateBase.h"

#include "Actor/LowpolyCharacter.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Utils/LowpolyPlayerContorller.h"



// Sets default values for this component's properties
UFSMComponent::UFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	StartState = ECharacterState::ECS_Idle;
	bCanInput = true;

	animationSpeed = 1.0f;
	// ...
}


// Called when the game starts
void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (currentState != nullptr)
	{
		currentState->Update(DeltaTime);
	}
	// ...
}

void UFSMComponent::Start()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Attack%d Init!!"), StateArray.Num()));
	if (ownedCharacter == nullptr)
	{
		AActor* pawn = GetOwner();

		//if (pawn == nullptr) return;

		ownedCharacter = Cast<ALowpolyCharacter>(pawn);
	}

	TArray<FStateData*> arrayData;
	StateData->GetAllRows(FString(""), arrayData);

	for (auto& data : arrayData)
	{
		if (data == nullptr) continue;
		if (data->StateClass == nullptr)
		{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Fail State "), StateArray.Num()));
			continue;
		}

		UStateBase* newState = NewObject<UStateBase>(this, data->StateClass);

		if (StateMap.Contains(newState->EState) == false)
		{
			newState->OwnedPlayer = ownedCharacter;
			newState->Init(*data);
			StateMap.Add(newState->EState, newState);

			UE_LOG(LogTemp, Warning, TEXT("Succed :"));

		}
	}

	PushState(StartState);
	//ChangeState(StartState);
}


UStateBase* UFSMComponent::FindState(ECharacterState eState)
{
	if (StateMap.Num() == 0) return nullptr;

	UStateBase** stateBase = StateMap.Find(eState);

	return stateBase == nullptr ? nullptr : *stateBase;
}


void UFSMComponent::HandleInput(EInputEvent Input, FKey key, float axisValue)
{
	if (bCanInput == false) return;
	if (ownedCharacter->GetCharacterMovement()->IsFalling()) return;
	if (ownedCharacter->GetInventoryVisiblity() == ESlateVisibility::Visible) return;

	if (currentState != nullptr)
	{
		currentState->HandleInput(Input, key, axisValue);
	}
}


bool UFSMComponent::ReleaseAndPushState(ECharacterState eState)
{
	UStateBase* newState = FindState(eState);

	if (newState == nullptr) return false;

	if (CheckEnterDelegate.Execute(newState) == false)
	{
		return false;
	}

	ReservePopState();
	ReservePushState(eState);

	return true;
	//bCanInput = false;
}

bool UFSMComponent::ChangeState(ECharacterState eState)
{
	
	UStateBase* newState  = FindState(eState);

	if (newState != nullptr)
	{
		if (CheckEnterDelegate.Execute(newState) == false)
		{
			return false;
		}

		if (currentState != nullptr)
		{
			currentState->Exit();
		}

		newState->Enter(animationSpeed);
		currentState = newState;


		return true;
	}
	else
	{
		//ChangeState(StartState);
		UE_LOG(LogTemp, Warning, TEXT("Not have a State Key "));
	}


	return false;

}

bool UFSMComponent::PushState(ECharacterState eState)
{
	UStateBase* newState = FindState(eState);

	if (newState != nullptr)
	{
		if (CheckEnterDelegate.Execute(newState) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail!!"));
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Good!!"));
		}

		StateStack.Push(newState);
		topState = StateStack.Top();
		PlayTopState();
		                                                                                                                                                 
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not have a State Key"));
	}

	return false;
}

bool UFSMComponent::PushState_float(ECharacterState eState, float _consumeStamina)
{
	UStateBase* newState = FindState(eState);

	if (newState != nullptr)
	{
		if (CheckEnterDelegate_float.Execute(_consumeStamina) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail!!"));
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Good!!"));
		}

		StateStack.Push(newState);
		topState = StateStack.Top();
		PlayTopState();

		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not have a State Key"));
	}

	return false;
}

void UFSMComponent::PlayTopState()
{
	if (currentState != nullptr)
	{
		currentState->Exit();
	}
	
	auto state = StateStack.Top();

	if (state != nullptr)
	{
		state->Enter(animationSpeed);
		currentState = state;
	}
	else
	{
		ChangeState(StartState);
		UE_LOG(LogTemp, Warning, TEXT("Not have a Top State Key"));
	}
}

void UFSMComponent::ReservePushState(ECharacterState eState)
{
	UStateBase* newState = FindState(eState);

	if (newState != nullptr)
	{
		StateStack.Push(newState);
		topState = StateStack.Top();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not have a State Key"));
	}
}

void UFSMComponent::ReservePopState()
{
	if (StateStack.Num() > 0 && currentState != nullptr)
	{
		StateStack.Pop();
		topState = StateStack.Top();
	}
}

void UFSMComponent::PopState()
{
	if (StateStack.Num() > 0 && currentState != nullptr)
	{
		StateStack.Pop();

		if (StateStack.Num() > 0)
			topState = StateStack.Top();
		else
			topState = nullptr;

		PlayTopState();
	}
}

void UFSMComponent::PopAllState()
{
	while (StateStack.Num() > 0)
	{
		StateStack.Pop();
	}

	ReservePushState(StartState);
}

ECharacterState UFSMComponent::GetState()
{
	return currentState == nullptr ? ECharacterState::ECS_None : currentState->EState;
}

float UFSMComponent::GetDamaged(EAttackType attackType ,FVector attackPosition, float DMG)
{
	if (currentState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("i'm Not have a State!!!"));
		return 0.0f;
	}

	return currentState->Damaged(attackType, attackPosition, DMG);
}

