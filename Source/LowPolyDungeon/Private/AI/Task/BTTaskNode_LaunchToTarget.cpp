// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTaskNode_LaunchToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/LowpolyAIController.h"

#include "Actor/LowpolyCharacter.h"
#include "Actor/AICharacterBase.h"

#include "Engine/World.h"

#include "Kismet/KismetMathLibrary.h"

#include "TimerManager.h"
#include "Engine/World.h"

UBTTaskNode_LaunchToTarget::UBTTaskNode_LaunchToTarget()
{
	TimeCount = 0;
	isSliding = true;
}


EBTNodeResult::Type UBTTaskNode_LaunchToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* controllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (controllingPawn == nullptr) return EBTNodeResult::Failed;

	AAICharacterBase* character = Cast<AAICharacterBase>(controllingPawn);

	if (character == nullptr)
		return EBTNodeResult::Failed;

	auto target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ALowPolyAIController::TargetKey);

	ALowpolyCharacter* targetCharacter = Cast<ALowpolyCharacter>(target);

	if (targetCharacter == nullptr)
		return EBTNodeResult::Failed;

	TimeCount += GetWorld()->GetDeltaSeconds();

	if (TimeCount > 0.5f )
	{
		return EBTNodeResult::Failed;
	}
	FVector pos = targetCharacter->GetActorLocation();

	FVector result = FMath::VInterpTo(character->GetActorLocation(), pos, GetWorld()->GetDeltaSeconds(), 1.0f);

	character->SetActorLocation(result, true);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Real"));
	
	bNotifyTick = true;
	
	return EBTNodeResult::Succeeded;
}


