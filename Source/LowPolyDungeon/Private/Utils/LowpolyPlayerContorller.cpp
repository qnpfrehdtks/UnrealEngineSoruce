// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/LowpolyPlayerContorller.h"
#include "Widget/InventoryUserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundCue.h"


ALowpolyPlayerContorller::ALowpolyPlayerContorller()
{

}

void ALowpolyPlayerContorller::BeginPlay()
{
	Super::BeginPlay();

	InventoryWidget = CreateWidget<UInventoryUserWidget>(this, IneventoryWidgetClass);
	DyingWidget = CreateWidget<UUserWidget>(this, DyingWidgetClass);
	VictoryWidget = CreateWidget<UUserWidget>(this, VictoryWidgetClass);

//	FInputModeGameAndUI Mode;
//	Mode.SetHideCursorDuringCapture(false);
//	SetInputMode(Mode);

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ReticleSize(DyingWidget->GetDesiredSize().X, DyingWidget->GetDesiredSize().Y);

	const float CenterX = ViewportSize.X / 2.0f;
	const float CenterY = ViewportSize.Y / 2.0f;
	const float ReticleCenterX = ReticleSize.X / 2.0f;
	const float ReticleCenterY = ReticleSize.Y / 2.0f;

	InventoryWidget->AddToViewport(9999);
	InventoryWidget->SetPositionInViewport(FVector2D(80, 80));
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);

	DyingWidget->AddToViewport(10000);
	DyingWidget->SetPositionInViewport(FVector2D(CenterX - ReticleSize.X, CenterY - ReticleCenterY));
	DyingWidget->SetVisibility(ESlateVisibility::Hidden);

	VictoryWidget->AddToViewport(10000);
	VictoryWidget->SetPositionInViewport(FVector2D(CenterX - ReticleSize.X, CenterY - ReticleCenterY));
	VictoryWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ALowpolyPlayerContorller::SetVisibleInventory_Implementation(bool value)
{
	if (value)
	{
		FInputModeGameAndUI uiGameOnly;
		
		SetInputMode(uiGameOnly);
		InventoryWidget->OpenInventory();
		bShowMouseCursor = true;
	}
	else
	{
		FInputModeGameOnly gameOnly;
		SetInputMode(gameOnly);
		InventoryWidget->CloseInventory();
		bShowMouseCursor = false;
	}
}

void ALowpolyPlayerContorller::ToggleInventoryUI()
{
	ESlateVisibility state = InventoryWidget->GetVisibility();
	switch (state)
	{
	case ESlateVisibility::Visible:
		SetVisibleInventory_Implementation(false);
		break;
	case ESlateVisibility::Hidden:
		SetVisibleInventory_Implementation(true);
		break;
	default:
		break;
	}

}


