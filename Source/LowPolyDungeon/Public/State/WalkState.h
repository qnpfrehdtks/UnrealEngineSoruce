// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/StateBase.h"
#include "Enums/CharacterEnums.h"
#include "WalkState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOWPOLYDUNGEON_API UWalkState : public UStateBase
{
	GENERATED_BODY()

public:
	UWalkState();

	virtual void Init_Implementation(const FStateData& newData) override;
	virtual void HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue) override;
	virtual void Enter_Implementation(float animationplayRate) override;
	virtual void Update_Implementation(float DeltaTime) override;
	virtual void Exit_Implementation() override;
	virtual float Damaged(EAttackType dmgType, FVector dmgPosition, float DMG) override;
	
};
