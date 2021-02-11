// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StateDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LOWPOLYDUNGEON_API UStateDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UStateDataAsset();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	bool bCanMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float consumeStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float plusStaminaPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	class UAnimMontage* montage;


};
