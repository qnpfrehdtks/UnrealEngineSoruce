// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemEnums.h"
#include "InvenItemStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UInvenItemStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;



private:
	UPROPERTY()
	class UImage* ItemIconImage;

	UPROPERTY()
	class UImage* ItemStatBGImage;

	UPROPERTY()
	class UTextBlock* ItemNameText;

	UPROPERTY()
	class UTextBlock* ItemDescText;

	UPROPERTY()
	class UTextBlock* ItemStatText;

	void SetItemDesc(FString itemText);
	void SetItemImage(class UTexture2D* ItemTexture);
	void SetItemStatText( class AItemBase* item);
	void SetItemName(AItemBase* item);
public:
	void SetItemData(class AItemBase* item);

	UFUNCTION(BlueprintCallable)
	void BeginPlay();

};
