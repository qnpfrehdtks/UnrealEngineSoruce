// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GetItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UGetItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UWidgetAnimation* WidgetAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation | Sound")
	class USoundCue* GetItemSound;



	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent)
	void ShowWidget(class UTexture2D* ItemTexture,const FString& itemText);
	virtual void ShowWidget_Implementation(class UTexture2D* ItemTexture, const FString& itemText);

	UFUNCTION(BlueprintCallable)
	void SetItemImage(class UTexture2D* ItemTexture);

	UFUNCTION(BlueprintCallable)
	void ShowGetItemWidget(class UTexture2D* ItemTexture, const FString& itemText, float showTime = 3.0f);

	UFUNCTION(BlueprintCallable)
	void UnShowGetItemWidget();

	UFUNCTION(BlueprintCallable)
	void SetItemName(FString itemText);

	FTimerHandle GetitemTimer;
};
