// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/InteractiveActorBase.h"
#include "InteractiveStepWall.generated.h"

/**
 * 
 */
/* 캐릭터랑 상호작용시 문을 엽니다. */
UCLASS()
class LOWPOLYDUNGEON_API AInteractiveStepWall : public AInteractiveActorBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AInteractiveStepWall();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	UParticleSystem* InteractParticle;

	virtual bool OnStartInteractive_Implementation(AActor* actor) override;
};
