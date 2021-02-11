// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventorySlotWidget.h"
#include "Components/Image.h"
#include "Actor/ItemBase.h"
#include "Components/TextBlock.h"

#include "Actor/LowpolyCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "Animation/WidgetAnimation.h"


void UInventorySlotWidget::NativeConstruct()
{
	EquippedMarkImage = Cast<UImage>(GetWidgetFromName(TEXT("EquippedImage")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	selectedImage =  Cast<UImage>(GetWidgetFromName(TEXT("Selected")));
	SetItemImage(nullptr);
	SetTextBlock("");
	SetActiveEquippedImage(false);

	if(selectedImage)
	selectedImage->SetVisibility(ESlateVisibility::Hidden);
}

bool UInventorySlotWidget::Initialize()
{
	Super::Initialize();

	return true;
}

void UInventorySlotWidget::SetActiveEquippedImage(bool value)
{
	value == true ? EquippedMarkImage->SetVisibility(ESlateVisibility::Visible) : EquippedMarkImage->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlotWidget::OnUnSelectSlot()
{
	selectedImage->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlotWidget::OnSelectSlot()
{
	if (refItemBase == nullptr)
	{
		selectedImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	selectedImage->SetVisibility(ESlateVisibility::Visible);
	OnSelectSlotDelegate.Broadcast(refItemBase, this);
}

void UInventorySlotWidget::SetItemImage(UTexture2D* ItemTexture)
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

void UInventorySlotWidget::SetTextBlock(FString itemText)
{
	if ( itemText.IsEmpty())
	{
		ItemText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	ItemText->SetVisibility(ESlateVisibility::Visible);
	ItemText->SetText(FText::FromString(itemText));
}

void UInventorySlotWidget::SetItemData(AItemBase* item)
{
	if (item == nullptr)
	{
		SetItemImage(nullptr);
		SetTextBlock("");
		SetActiveEquippedImage(false);
		refItemBase = nullptr;
		return;
	}

	refItemBase = item;

	SetItemImage(item->GetTexture2D());
	item->IsEquippedItem() == true ? SetActiveEquippedImage(true) : SetActiveEquippedImage(false);
	item->IsStackCount() == true ? SetTextBlock(FString::FromInt(item->GetCount())) : SetTextBlock("");

}


