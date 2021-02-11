// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_CheckDistance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/LowpolyAIController.h"
#include "Engine/World.h"

UBTService_CheckDistance::UBTService_CheckDistance()
{

}

void UBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AActor* controllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (controllingPawn == nullptr) return;

	auto target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ALowPolyAIController::TargetKey);

	if (target == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ALowPolyAIController::TargetDistanceKey, 99999.0f);
		return;
	}
	AActor* actor = Cast<AActor>(target);

	float distance = FVector::Distance(actor->GetActorLocation(), controllingPawn->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ALowPolyAIController::TargetDistanceKey, distance);
	UE_LOG(LogTemp, Warning, TEXT(" , Distance : %f"), distance);
}