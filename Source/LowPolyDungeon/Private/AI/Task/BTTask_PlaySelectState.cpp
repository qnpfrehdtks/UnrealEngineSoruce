// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_PlaySelectState.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/LowpolyAIController.h"

#include "Actor/LowpolyCharacter.h"
#include "Actor/AICharacterBase.h"

#include "Engine/World.h"

#include "TimerManager.h"
#include "Engine/World.h"

#include "Enums/CharacterEnums.h"
#include "Component/FSMComponent.h"

UBTTask_PlaySelectState::UBTTask_PlaySelectState()
{
	isDelayTime = false;
	bNotifyTick = true;


}

void UBTTask_PlaySelectState::DelayTimer()
{
	isDelayTime = false;
}

EBTNodeResult::Type UBTTask_PlaySelectState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* controllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (controllingPawn == nullptr) return EBTNodeResult::Failed;

	Character = Cast<AAICharacterBase>(controllingPawn);

	if (Character == nullptr)
		return EBTNodeResult::Failed;

	if (isDelayTime == false)
	{
		int32 idx = FMath::RandRange(0, arrayState.Num() - 1);
		Character->PlayForceState(arrayState[idx]);
		if(DelayTime > 0.1f)
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_PlaySelectState::DelayTimer, DelayTime);
	}
	isDelayTime = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_PlaySelectState::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (Character == nullptr) return;
	if (Character->FSM == nullptr) return;

	if (!isDelayTime)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}