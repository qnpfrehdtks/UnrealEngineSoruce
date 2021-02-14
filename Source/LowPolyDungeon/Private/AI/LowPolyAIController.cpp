// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/LowPolyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

#include "DrawDebugHelpers.h"
#include "Actor/LowpolyCharacter.h"

const FName ALowPolyAIController::TargetDistanceKey(TEXT("TargetDistanceKey"));
const FName ALowPolyAIController::TargetKey(TEXT("UpdatedActor"));
const FName ALowPolyAIController::CanAttackKey(TEXT("IsCanAttack"));

ALowPolyAIController::ALowPolyAIController()
{
	SetGenericTeamId(FGenericTeamId(10));
}

void ALowPolyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UseBlackboard(BlackboardToUse, BBComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Success!! AI  USE BB"));
	}

	RunBehaviorTree(BehaviorTreeToUse);

	AIPerception = GetAIPerceptionComponent();
	if (AIPerception != nullptr)
	{
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ALowPolyAIController::SenseStuff);
	}
}

void ALowPolyAIController::SenseStuff(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	// We set Focalpoint if the sense was successfull
	if (Stimulus.WasSuccessfullySensed())
	{
		ALowpolyCharacter* character = Cast<ALowpolyCharacter>(UpdatedActor);
		if (character)
		{
			BBComponent->SetValueAsObject("UpdatedActor", UpdatedActor);

			UE_LOG(LogTemp, Warning, TEXT("Sensing Actor : %s"), *UpdatedActor->GetName());
		}
		else
		{
			BBComponent->SetValueAsObject("UpdatedActor", nullptr);
		}

	}
	else
	{
		BBComponent->SetValueAsObject("UpdatedActor", nullptr);
		UE_LOG(LogTemp, Warning, TEXT("Ain't sensing anything"));
	}
}

ETeamAttitude::Type ALowPolyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) 
	{
		//OR CUSTOM BEHAVIOUR--------------------------------------------------
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn))
		{
			//Create an alliance with Team with ID 10 and set all the other teams as Hostiles:
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			if (OtherTeamID == 10) 
			{
				/* 팀아이디가 10이면 중립*/
				return ETeamAttitude::Neutral;
			}
			else 
			{
				return ETeamAttitude::Hostile;
			}
		}
	}

	return ETeamAttitude::Neutral;
}
