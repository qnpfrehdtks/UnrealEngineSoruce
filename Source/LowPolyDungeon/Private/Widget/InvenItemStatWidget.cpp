// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InvenItemStatWidget.h"
#include "Components/Image.h"
#include "Actor/ItemBase.h"
#include "Components/TextBlock.h"

#include "Actor/LowpolyCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "Animation/WidgetAnimation.h"

bool UInvenItemStatWidget::Initialize()
{
	Super::Initialize();

	ItemNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemStatBGImage = Cast<UImage>(GetWidgetFromName(TEXT("StatBG")));
	ItemDescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDesc")));
	ItemStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemStat")));

	BeginPlay();

	return false;
}

void UInvenItemStatWidget::SetItemDesc(FString itemText)
{
	if (itemText.IsEmpty())
	{
		ItemDescText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	ItemDescText->SetVisibility(ESlateVisibility::Visible);
	ItemDescText->SetText(FText::FromString(itemText));
}

void UInvenItemStatWidget::SetItemImage(UTexture2D* ItemTexture)
{
	if (ItemTexture == nullptr)
	{
		ItemIconImage->SetBrushFromTexture(nullptr);
		ItemIconImage->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("hidden TExture"));
		return;
	}

	ItemIconImage->SetVisibility(ESlateVisibility::Visible);
	ItemIconImage->SetBrushFromTexture(ItemTexture);
}

void UInvenItemStatWidget::SetItemStatText(AItemBase* item)
{
	if (item == nullptr)
	{
		ItemStatText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	ItemStatText->SetVisibility(ESlateVisibility::Visible);

	TMap<FString, float>& map = item->GetItemMap();

	FString resultStr = "";
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemClass"), true);
	if (!enumPtr)
	{
		resultStr = "[UnKnown]\n";
	}
	else
	{
		switch (item->GetItemClass())
		{
		case EItemClass::EIC_Normal:
			resultStr.Append("[Normal]\n");
			break;
		case EItemClass::EIC_Rare:
			resultStr.Append("[Rare]\n");
			break;
		case EItemClass::EIC_Unique:
			resultStr.Append("[Unique]\n");
			break;
		case EItemClass::EIC_Legend:
			resultStr.Append("[Legendary]\n");
			break;
		}
	}

	for (auto& iter : map)
	{
		resultStr = resultStr.Append(FString::Printf(TEXT("%s : %.1f\n"), *iter.Key, iter.Value));
	}


	ItemStatText->SetText(FText::FromString(resultStr));
}

void UInvenItemStatWidget::SetItemName(AItemBase* item)
{
	if (item == nullptr)
	{
		ItemStatBGImage->SetVisibility(ESlateVisibility::Hidden);
		ItemNameText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	FString resultStr = "";
	FSlateColor newColor = FSlateColor(FLinearColor::White);

	switch (item->GetItemClass())
	{
	case EItemClass::EIC_Normal:
		newColor = FSlateColor(FLinearColor::Gray);
		break;
	case EItemClass::EIC_Rare:
		newColor = FSlateColor(FLinearColor::Yellow);
		break;
	case EItemClass::EIC_Unique:
		newColor = FSlateColor(FColor::Purple);
		break;
	case EItemClass::EIC_Legend:
		newColor = FSlateColor(FColor::Orange);
		break;
	}
	ItemStatBGImage->SetVisibility(ESlateVisibility::Visible);
	ItemNameText->SetVisibility(ESlateVisibility::Visible);

	ItemStatBGImage->SetColorAndOpacity(newColor.GetSpecifiedColor());
	ItemNameText->SetColorAndOpacity(newColor);
	ItemNameText->SetText(FText::FromString(item->GetItemName()));
}

void UInvenItemStatWidget::SetItemData(AItemBase* item)
{
	if (item == nullptr)
	{
		SetItemStatText(nullptr);
		SetItemImage(nullptr);
		SetItemDesc("");
		SetItemName(nullptr);
		return;
	}

	SetItemStatText(item);
	SetItemName(item);
	SetItemDesc(item->GetItemDesc());
	SetItemImage(item->GetTexture2D());
}

void UInvenItemStatWidget::BeginPlay()
{
}
