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

	/* �κ��丮 Widget Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Inventory")
	TSubclassOf<class UInventoryUserWidget> IneventoryWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryUserWidget* InventoryWidget;


	/* ����� �޼��� Widget Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> DyingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UUserWidget* DyingWidget;

	/* �¸��� �޼��� Widget Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> VictoryWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UUserWidget* VictoryWidget;

	/* ����� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* DyingSoundCue;

	/* �¸��� ���� */
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
