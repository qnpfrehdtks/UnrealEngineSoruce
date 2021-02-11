// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MinionMeleeAttack.h"
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

UBTTask_MinionMeleeAttack::UBTTask_MinionMeleeAttack()
{
	isAttacking = false;
	bNotifyTick = true;
}

void UBTTask_MinionMeleeAttack::AttackTimer()
{
	isAttacking = false;
}

EBTNodeResult::Type UBTTask_MinionMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* controllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (controllingPawn == nullptr) return EBTNodeResult::Failed;

	if(AIBase == nullptr)
		AIBase = Cast<AAICharacterBase>(controllingPawn);

	if(AIBase == nullptr)
		return EBTNodeResult::Failed;

	if (isAttacking == false)
	{
		int32 idx = FMath::RandRange(0,arrayState.Num() - 1);
		AIBase->SelectState(arrayState[idx]);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_MinionMeleeAttack::AttackTimer, 1.0f );
	}
	isAttacking = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_MinionMeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (AIBase == nullptr) return;
	if (AIBase->FSM == nullptr) return;

	if(AIBase->FSM->GetState() != ECharacterState::ECS_Attack1
		&& AIBase->FSM->GetState() != ECharacterState::ECS_Attack2
		&& AIBase->FSM->GetState() != ECharacterState::ECS_Attack3
		&& AIBase->FSM->GetState() != ECharacterState::ECS_Attack4
		&& AIBase->FSM->GetState() != ECharacterState::ECS_Attack5
		&& AIBase->FSM->GetState() != ECharacterState::ECS_Attack6 
		&& !isAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
}
