// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LowpolyPlayerContorller.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API ALowpolyPlayerContorller : public APlayerController
{
	GENERATED_BODY()

public:
	ALowpolyPlayerContorller();

	/* 인벤토리 Widget Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Inventory")
	TSubclassOf<class UInventoryUserWidget> IneventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryUserWidget* InventoryWidget;


	/* 사망시 메세지 Widget Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> DyingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UUserWidget* DyingWidget;

	/* 승리시 메세지 Widget Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> VictoryWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UUserWidget* VictoryWidget;

	/* 사망시 사운드 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* DyingSoundCue;

	/* 승리시 사운드 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundCue* VictorySoundCue;


protected:
	virtual void BeginPlay() override;



public:

	UFUNCTION(BlueprintNativeEvent)
	void SetVisibleInventory(bool value);
	virtual void SetVisibleInventory_Implementation(bool value);

	void ToggleInventoryUI();

	UFUNCTION(BlueprintImplementableEvent)
	void VisibleDyingMessage(bool value);
	//virtual void VisibleDyingMessage_Implementation(bool value);

	UFUNCTION(BlueprintImplementableEvent)
	void VisibleVictoryMessage(bool value);
	//virtual void VisibleVictoryMessage_Implementation(bool value);
};
