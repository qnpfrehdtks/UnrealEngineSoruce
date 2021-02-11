// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GetItemWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Components/Image.h"
#include "Actor/ItemBase.h"
#include "Components/TextBlock.h"

#include "Animation/WidgetAnimation.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


void UGetItemWidget::NativeConstruct()
{
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("WeaponIcon")));
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("GetItemName")));

	SetVisibility(ESlateVisibility::Hidden);
}

void UGetItemWidget::ShowWidget_Implementation(UTexture2D* ItemTexture, const FString& itemText)
{
	SetItemImage(ItemTexture);
	SetItemName(itemText);

	SetVisibility(ESlateVisibility::Visible);

}

void UGetItemWidget::SetItemImage(UTexture2D* ItemTexture)
{
	if (ItemTexture == nullptr)
	{
		ItemImage->SetBrushFromTexture(nullptr);
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("hidden TExture"));
		return;
	}

	ItemImage->SetVisibility(ESlateVisibility::Visible);
	ItemImage->SetBrushFromTexture(ItemTexture);
}

void UGetItemWidget::ShowGetItemWidget(UTexture2D* ItemTexture, const FString& itemText, float showTime)
{
	if (WidgetAnimation != nullptr)
	{
		PlayAnimationForward(WidgetAnimation);
		GetWorld()->GetTimerManager().SetTimer(GetitemTimer, this, &UGetItemWidget::UnShowGetItemWidget, showTime);
	}

	UGameplayStatics::PlaySound2D(GetWorld(), GetItemSound, 2.0f);

	ShowWidget_Implementation(ItemTexture, itemText);
}

void UGetItemWidget::UnShowGetItemWidget()
{
	if (WidgetAnimation != nullptr)
	{
		PlayAnimationReverse(WidgetAnimation);
	}
}

void UGetItemWidget::SetItemName(FString itemText)
{
	if (itemText.IsEmpty())
	{
		ItemName->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	ItemName->SetVisibility(ESlateVisibility::Visible);
	ItemName->SetText(FText::FromString(itemText));
}
