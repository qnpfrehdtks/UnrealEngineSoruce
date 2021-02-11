// Copyright Epic Games, Inc. All Rights Reserved.


#include "Utils/LowPolyDungeonGameModeBase.h"
#include "Blueprint/UserWidget.h"


ALowPolyDungeonGameModeBase::ALowPolyDungeonGameModeBase()
{

}

void ALowPolyDungeonGameModeBase::SetBattleModeUIVisible(bool value)
{
	if (StartingWidgetClass != nullptr)
	{
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->SetVisibility(value == true ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
	}
}



void ALowPolyDungeonGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (StartingWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), StartingWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}


