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
	// 인벤토리를 업데이트해주는 함수.
	UFUNCTION()
	void UpdateInventory();

	// 인벤토리에 아이템을 넣는다.
	UFUNCTION()
	void InsertInventory(class AItemBase* item);

	// 인벤토리에서 아이템을 제거한다.
	UFUNCTION()
	void RemoveInventory(class AItemBase* item);

	// 인벤토리가 가득찻는가?
	UFUNCTION()
	bool IsFullInventory();

	// 인벤토리에서 아이템을 가져온다.
	UFUNCTION()
	AItemBase* GetItemFromInventory(int32 itemID);

	// 인벤토리 Map 구조를 가져옵니다.
	UFUNCTION()
	FORCEINLINE TMap<int32, AItemBase*> GetInventoryArray() { return mapItemInventory; }
		
};
