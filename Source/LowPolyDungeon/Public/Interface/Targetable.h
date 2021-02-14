// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Targetable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
 /* 타겟이 가능한 오브젝트일 경우 구현해서 사용하세요. */
class LOWPOLYDUNGEON_API ITargetable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	ITargetable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void OnStartTargeting(AActor* actor);
	virtual void OnStartTargeting_Implementation(AActor* actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	void OnEndTargeting(AActor* actor);
	virtual void OnEndTargeting_Implementation(AActor* actor);
};
