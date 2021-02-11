// Fill out your copyright notice in the Description page of Project Settings.



#include "..\..\Public\Widget\PlayerHUDWidget.h"
#include "Widget/GetItemWidget.h"

void  UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UPlayerHUDWidget::Initialize()
{
	return Super::Initialize();
}

void UPlayerHUDWidget::ShowGetItemWidget(UTexture2D* textue, const FString& itemName)
{
	getItemWidget->SetVisibility(ESlateVisibility::Visible);
}


