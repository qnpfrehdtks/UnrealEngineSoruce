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
	if (ownedCharacter == nullptr)
	{
		AActor* pawn = GetOwner();

		//if (pawn == nullptr) return;

		ownedCharacter = Cast<ALowpolyCharacter>(pawn);
	}

	TArray<FStateData*> arrayData;
	StateData->GetAllRows(FString(""), arrayData);

	/* DataTable 에서 이 캐릭터가 행동할 State들을 가져온다. */
	for (auto& data : arrayData)
	{
		if (data == nullptr) continue;
		if (data->StateClass == nullptr)
		{
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

	StartState = ECharacterState::ECS_Idle;
	bCanInput = true;

	/* Idle 실행 */
	ChangeState(StartState);
}

void UFSMComponent::ReserveState(ECharacterState eState)
{
	ResverdState = eState;
}

/* State 값 가져온다. */
UStateBase* UFSMComponent::FindState(ECharacterState eState)
{
	if (StateMap.Num() == 0) return nullptr;

	UStateBase** stateBase = StateMap.Find(eState);

	return stateBase == nullptr ? nullptr : *stateBase;
}

/* 캐릭터의 인풋에 따른 처리를 여기에서 진행함. */
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
		ChangeState(StartState);
		UE_LOG(LogTemp, Warning, TEXT("Not have a State Key "));
	}

	return false;
}

bool UFSMComponent::PlayReserveState()
{
	if (ResverdState == ECharacterState::ECS_None) return false;

	bool result = ChangeState(ResverdState);
	ResverdState = ECharacterState::ECS_None;
	return result;

}

bool UFSMComponent::ChangeState_float(ECharacterState eState, float _consumeStamina)
{

	UStateBase* newState = FindState(eState);

	if (newState != nullptr)
	{
		if (CheckEnterDelegate_float.Execute(_consumeStamina) == false)
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
		ChangeState(StartState);
		UE_LOG(LogTemp, Warning, TEXT("Not have a State Key "));
	}


	return false;

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

	/* 데미지를 입는 이벤트 발생시 현재 스테이트에 전달한다. */
	return currentState->Damaged(attackType, attackPosition, DMG);
}

