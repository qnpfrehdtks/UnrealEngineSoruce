// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_LaunchToTarget.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UBTTaskNode_LaunchToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_LaunchToTarget();

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	float TimeCount;

	bool isSliding;

};

