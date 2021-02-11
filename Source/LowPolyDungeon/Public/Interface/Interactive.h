// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

UENUM(BlueprintType)
enum class EInteractiveType : uint8
{
	EIT_NONE UMETA(DisplayName = "None"),
	EIT_NPC UMETA(DisplayName = "NPC"),
	EIT_SOUL UMETA(DisplayName = "Soul"),
	EIt_MAX UMETA(DisplayName = "Max")
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOWPOLYDUNGEON_API IInteractive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IInteractive();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactive")
	bool OnStartInteractive(AActor* actor);
	virtual bool OnStartInteractive_Implementation(AActor* actor);

};
