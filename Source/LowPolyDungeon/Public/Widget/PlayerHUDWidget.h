// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

public:
	UPROPERTY(EditDefaultsOnly ,BlueprintReadOnly, Category = "GetItemWidget")
	class UGetItemWidget* getItemWidget;

	UFUNCTION(BlueprintCallable)
	void ShowGetItemWidget(class UTexture2D* textue, const FString& itemName);

};
