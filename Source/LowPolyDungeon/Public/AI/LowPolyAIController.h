// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AiPerceptionComponent.h"
#include "LowPolyAIController.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API ALowPolyAIController : public AAIController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
public:
	ALowPolyAIController();
	
	// We can set Blackboard in BP
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	class UBlackboardData* BlackboardToUse;

	// We can set BehaviorTree in BP
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	class UBehaviorTree* BehaviorTreeToUse;

	// This is the Blackboardcomponent that will be as Return value later. 
	UPROPERTY()
	class UBlackboardComponent* BBComponent;

	// Perception component. 
	/* AI가 소리,시야 탐지등에 쓰이는 컴포넌트*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionComponent* AIPerception;

	/* AISensse 주변에 사운드가 탐지되면 반응한다. */
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	TSubclassOf<class UAISense> HearingSense;

	/* AISense 시야각에 적이 들어오면 탐지한다. */
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	TSubclassOf<class UAISense> SightSense;

public:
	// Main function, when sensing stuff.
	UFUNCTION()
	void SenseStuff(AActor* UpdatedActor, FAIStimulus Stimulus);

	static const FName TargetDistanceKey;
	static const FName TargetKey;
	static const FName CanAttackKey;

public:
	// Override this function 
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
};
