// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelecteSlot, class AItemBase*, class UInventorySlotWidget*);
/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	UImage* EquippedMarkImage;

	UPROPERTY()
	class UTextBlock* ItemText;

	UPROPERTY()
	AItemBase* refItemBase;

	UPROPERTY()
	UImage* selectedImage;

	void SetActiveEquippedImage(bool value);
	void SetItemImage(class UTexture2D* ItemTexture);
	void SetTextBlock(FString itemText);
public:
	FOnSelecteSlot OnSelectSlotDelegate;

	UFUNCTION(BlueprintPure)
	FORCEINLINE AItemBase* GetItmeBase() { return refItemBase; }

	UFUNCTION(BlueprintCallable)
	void SetItemData(class AItemBase* item);

	UFUNCTION(BlueprintCallable)
	void OnSelectSlot();

	UFUNCTION(BlueprintCallable)
	void OnUnSelectSlot();
};
