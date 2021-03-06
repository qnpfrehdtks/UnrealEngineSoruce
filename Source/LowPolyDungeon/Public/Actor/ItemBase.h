// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/CharacterEnums.h"
#include "Enums/ItemEnums.h"

#include "Interface/Equipable.h"

#include "Engine/DataTable.h"

#include "ItemBase.generated.h"


UCLASS()
class LOWPOLYDUNGEON_API AItemBase : public AActor, public IEquipable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	static int32 itemRespawnCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class ALowpolyCharacter* ownedCharacter;

	/* */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UCapsuleComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* StaticItemMesh;

	/* 아이템 데이터를 가져와 초기화 진행한다. */
	UFUNCTION()
	void InitializeItemDate();

	/* 아이템 사용 */
	UFUNCTION(BlueprintNativeEvent)
	void UseItem(int32 index);
	virtual void UseItem_Implementation(int32 index);

	/* Bone 소켓네임을 찾아 부탁한다. */
	UFUNCTION(BlueprintCallable)
	void AttachToMesh_ByName(class USkeletalMeshComponent* mesh, FName SocketName);

	/* 그냥 메시에 부착한다. */
	UFUNCTION(BlueprintCallable)
	void AttachToMesh(class USkeletalMeshComponent* mesh);

	UFUNCTION()
	void PlayEquipItemSound();

	UFUNCTION(BlueprintCallable)
	void SetVisibleItemVisible(bool active);

	UFUNCTION(BlueprintPure)
	FORCEINLINE class UTexture2D* GetTexture2D() { return itemData.ItemTexture; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetItemUniqueID() { return uniqueItemID; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetItemID() { return ItemID; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE EItemType GetItemType() { return itemData.ItemType; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetItemName() { return itemData.ItemName; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetItemDesc() { return itemData.ItemDesc; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCount() { return itemData.Count; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsStackCount() { return itemData.bIsCount; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEquippedItem() { return isEquipped; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetSocketName() { return itemData.EquipSocket; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE EItemClass GetItemClass() { return itemData.eItemClass; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE TMap<FString, float>& GetItemMap() { return itemData.mapAttribute; }

protected:
	/* 아이템 데이터 정보 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FInventoryItemData itemData;

	/* 아이템 ID */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 ItemID;

	/* 아이템 UID */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 uniqueItemID;

	/* 장착되었나? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	bool isEquipped;

	

	// ----- interface 구현 --------
	virtual void OnEquip_Implementation(class USkeletalMeshComponent* mesh) override;
	virtual void OnEquip_EquipType_Implementation(class USkeletalMeshComponent* mesh, FName SocketName) override;
	virtual void OnDetach_Implementation() override;
};
