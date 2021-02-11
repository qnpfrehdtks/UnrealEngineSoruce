// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TMap<int32, class AItemBase*> mapItemInventory;

public:	
	UFUNCTION()
	void UpdateInventory();

	UFUNCTION()
	void InsertInventory(class AItemBase* item);

	UFUNCTION()
	void RemoveInventory(class AItemBase* item);

	UFUNCTION()
	bool IsFullInventory();

	UFUNCTION()
	AItemBase* GetItemFromInventory(int32 itemID);

	UFUNCTION()
	FORCEINLINE TMap<int32, AItemBase*> GetInventoryArray() { return mapItemInventory; }
		
};
