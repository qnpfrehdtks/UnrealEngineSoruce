// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/InteractiveActorBase.h"
#include "SoulItem.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API ASoulItem : public AInteractiveActorBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ASoulItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	UParticleSystem* InteractParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class TSubclassOf<class AItemBase> soulItemClass;

	virtual bool OnStartInteractive_Implementation(AActor* actor) override;
};
