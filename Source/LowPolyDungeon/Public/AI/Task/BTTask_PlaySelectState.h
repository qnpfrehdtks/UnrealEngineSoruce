// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enums/CharacterEnums.h"
#include "BTTask_PlaySelectState.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UBTTask_PlaySelectState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PlaySelectState();

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "state")
	TArray<ECharacterState> arrayState;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "state")
	float DelayTime;

	UFUNCTION()
	void DelayTimer();

	FTimerHandle TimerHandle;

	UPROPERTY()
	bool isDelayTime;


	UPROPERTY()
	AAICharacterBase* Character;

	
};
