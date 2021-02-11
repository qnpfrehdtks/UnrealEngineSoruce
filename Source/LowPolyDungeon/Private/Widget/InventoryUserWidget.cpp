// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryUserWidget.h"
#include "Widget/InvenItemStatWidget.h"

#include "Components/UniformGridPanel.h"

#include "Widget/InventorySlotWidget.h"
#include "Actor/LowpolyCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "Actor/ItemBase.h"

void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();



 }

bool UInventoryUserWidget::Initialize()
{
	Super::Initialize();

	UUniformGridPanel* gridPanel = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("SlotGridePanel")));
	auto arrWidget = gridPanel->GetAllChildren();

	slotCount = arrWidget.Num();

	for (int32 i = 0; i < slotCount; i++)
	{
		if (arrWidget[i] == nullptr)
			continue;

		UInventorySlotWidget* slot = Cast<UInventorySlotWidget>(arrWidget[i]);
		slot->OnSelectSlotDelegate.AddLambda(
			[this](AItemBase* item, UInventorySlotWidget* selectedSlot)
			{
				if (selectedItemSlot != nullptr && selectedItemSlot != selectedSlot)
				{
					selectedItemSlot->OnUnSelectSlot();
					selectedItemSlot = nullptr;
				}

				itemStatWidget->SetItemData(item);
				selectedItemSlot = selectedSlot;
				
			}
		);

		arrInventorySlot.Add(slot);
	}

	UE_LOG(LogTemp, Warning, TEXT("Inventory Init Complete"));
	return true;
}

void UInventoryUserWidget::OpenInventory()
{
	if (selectedItemSlot != nullptr)
	{
		selectedItemSlot->OnUnSelectSlot();
		selectedItemSlot = nullptr;
	}

	itemStatWidget->SetItemData(nullptr);
	SetVisibility(ESlateVisibility::Visible);
}

void UInventoryUserWidget::CloseInventory()
{
	if (selectedItemSlot != nullptr)
	{
		selectedItemSlot->OnUnSelectSlot();
		selectedItemSlot = nullptr;
	}

	itemStatWidget->SetItemData(nullptr);
	SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryUserWidget::EquipSelectedItem()
{
	if (selectedItemSlot == nullptr) return;

	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	ALowpolyCharacter* playerCharacter = Cast<ALowpolyCharacter>(pawn);

	if (playerCharacter != nullptr )
	{
		playerCharacter->EquipItemFromInventory(selectedItemSlot->GetItmeBase()->GetItemUniqueID());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Equip Failed"));
	}
}

void UInventoryUserWidget::UnEquipSelectedItem()
{
	if (selectedItemSlot == nullptr) return;

	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	ALowpolyCharacter* playerCharacter = Cast<ALowpolyCharacter>(pawn);

	if (playerCharacter != nullptr)
	{
		playerCharacter->UnEquipItemFromInventory(selectedItemSlot->GetItmeBase()->GetItemUniqueID());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Equip Failed"));
	}
}


void UInventoryUserWidget::UpdateItemToInventory(TMap<int32, AItemBase*>& itemMap)
{
	TArray<AItemBase*> arrayItem;
	itemMap.GenerateValueArray(arrayItem);

	UE_LOG(LogTemp, Warning, TEXT("Inventory is slotCount %d"), slotCount);

	for (int32 i = 0; i < slotCount; i++)
	{
		if (arrayItem.Num() > i )
		{
			arrInventorySlot[i]->SetItemData(arrayItem[i]);
		}
		else
		{
			arrInventorySlot[i]->SetItemData(nullptr);
		}
	}
}


