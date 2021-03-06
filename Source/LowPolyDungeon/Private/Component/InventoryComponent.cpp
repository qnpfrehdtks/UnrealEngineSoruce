// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"
#include "Utils/LowPolyGameInstance.h"

#include "Utils/LowpolyPlayerContorller.h"
#include "Utils/LowPolyGameInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Widget/InventoryUserWidget.h"

#include "Actor/ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


void UInventoryComponent::UpdateInventory()
{
	// 인벤토리의 정보를 업데이트해준다.
	ALowpolyPlayerContorller* controller = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (controller != nullptr)
	{
		controller->InventoryWidget->UpdateItemToInventory(mapItemInventory);
	}
}

void UInventoryComponent::InsertInventory(class AItemBase* item)
{
	// 중복되는 아이템 Id는 리턴
	if (mapItemInventory.Find(item->GetItemUniqueID()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Duplicated Item ID "));
		return;
	}

	// 인벤토리가 가득 찻는가?
	if (IsFullInventory())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full!!"));
		return;
	}

	ALowpolyPlayerContorller* controller = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (controller != nullptr)
	{
		mapItemInventory.Add(item->GetItemUniqueID(), item);
		controller->InventoryWidget->UpdateItemToInventory(mapItemInventory);
	}
}


void UInventoryComponent::RemoveInventory(class AItemBase* item)
{
	// 인벤토리에서 해당 아이템을 제거한다.
	if (mapItemInventory.Find(item->GetItemUniqueID()))
	{
		ALowpolyPlayerContorller* controller = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (controller != nullptr)
		{
			mapItemInventory.Remove(item->GetItemUniqueID());
			controller->InventoryWidget->UpdateItemToInventory(mapItemInventory);
		}
	}
}

bool UInventoryComponent::IsFullInventory()
{
	ALowpolyPlayerContorller* controller = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (controller != nullptr)
	{
		return mapItemInventory.Num() >= controller->InventoryWidget->GetSlotCount();
	}

	return true;
}

AItemBase* UInventoryComponent::GetItemFromInventory(int32 itemID)
{
	AItemBase** item = mapItemInventory.Find(itemID);
	return (item) == nullptr ? (nullptr) : *item;
}




