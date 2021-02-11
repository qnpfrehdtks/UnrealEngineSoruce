// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/LowpolyCharacter.h"
#include "Enums/CharacterEnums.h"
#include "AICharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API AAICharacterBase : public ALowpolyCharacter
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AAICharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
	ECharacterPhase currentPhase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particle")
	class UParticleSystem* rageParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Materials")
	class UMaterialInstance* matInstance;


	
	void Dead() override;
	void Attack() override;
	void SelectState(ECharacterState state);
	void PlayForceState(ECharacterState state);

	UFUNCTION()
	void ChangePhase(float healthRatio);

	// ====== 인터페이스 =======
	virtual void OnStartTargeting_Implementation(AActor* actor) override;
	
};
