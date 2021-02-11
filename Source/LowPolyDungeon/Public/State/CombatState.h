// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/StateBase.h"
#include "Enums/CharacterEnums.h"
#include "CombatState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable) // for blueprint to be able to be made as a blueprint class
class LOWPOLYDUNGEON_API UCombatState : public UStateBase
{
	GENERATED_BODY()

public:
	UCombatState();

	virtual void Init_Implementation(const FStateData& newData) override;
	virtual void HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue) override;
	virtual void Enter_Implementation(float animationplayRate) override;
	virtual void Update_Implementation(float DeltaTime) override;
	virtual void Exit_Implementation() override;
	virtual float Damaged(EAttackType dmgType, FVector dmgPosition, float DMG) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 attackCombo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float attackMult;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	//bool bCanInput;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	//UStateBase* NextState;
};
