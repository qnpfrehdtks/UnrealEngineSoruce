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
	// �κ��丮�� ������Ʈ���ִ� �Լ�.
	UFUNCTION()
	void UpdateInventory();

	// �κ��丮�� �������� �ִ´�.
	UFUNCTION()
	void InsertInventory(class AItemBase* item);

	// �κ��丮���� �������� �����Ѵ�.
	UFUNCTION()
	void RemoveInventory(class AItemBase* item);

	// �κ��丮�� �������°�?
	UFUNCTION()
	bool IsFullInventory();

	// �κ��丮���� �������� �����´�.
	UFUNCTION()
	AItemBase* GetItemFromInventory(int32 itemID);

	// �κ��丮 Map ������ �����ɴϴ�.
	UFUNCTION()
	FORCEINLINE TMap<int32, AItemBase*> GetInventoryArray() { return mapItemInventory; }
		
};
