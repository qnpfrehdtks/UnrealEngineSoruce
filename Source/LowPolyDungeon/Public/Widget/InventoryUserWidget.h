// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemEnums.h"
#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;


public:
	UFUNCTION(BlueprintCallable)
	void OpenInventory();

	UFUNCTION(BlueprintCallable)
	void CloseInventory();

	UFUNCTION(BlueprintCallable)
	void EquipSelectedItem();

	UFUNCTION(BlueprintCallable)
	void UnEquipSelectedItem();

	UFUNCTION(BlueprintCallable)
	void UpdateItemToInventory(TMap<int32, AItemBase*>& itemMap);

	FORCEINLINE int32 GetSlotCount() { return slotCount; }
	FORCEINLINE class UInventorySlotWidget* GetSelectedSlot() { return selectedItemSlot; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemSlot", meta = (AllowPrivateAccess = "true"));
	TArray<class UInventorySlotWidget*> arrInventorySlot;

	UPROPERTY()
	int32 slotCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemSlot", meta = (AllowPrivateAccess = "true"));
	class UInventorySlotWidget* selectedItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"));
	class UInvenItemStatWidget* itemStatWidget;
};
