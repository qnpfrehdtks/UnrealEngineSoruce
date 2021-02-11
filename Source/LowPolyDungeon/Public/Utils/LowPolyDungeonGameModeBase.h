// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LowPolyDungeonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API ALowPolyDungeonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALowPolyDungeonGameModeBase();

	UFUNCTION(BlueprintCallable)
	void SetBattleModeUIVisible(bool value);

	UFUNCTION(BlueprintImplementableEvent, Category = "Text")
	void SetWarningText(const FString& str, float time);

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<class UUserWidget> StartingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	UUserWidget* CurrentWidget;

};
