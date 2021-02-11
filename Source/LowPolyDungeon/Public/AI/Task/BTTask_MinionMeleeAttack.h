// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enums/CharacterEnums.h"
#include "BTTask_MinionMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UBTTask_MinionMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MinionMeleeAttack();

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "state")
	TArray<ECharacterState> arrayState;

	UFUNCTION()
	void AttackTimer();

	FTimerHandle TimerHandle;

	UPROPERTY()
	bool isAttacking;

	UPROPERTY()
	class AAICharacterBase* AIBase;
	
};
