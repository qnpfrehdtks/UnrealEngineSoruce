// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemEnums.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_NONE UMETA(DisplayName = "None"),
	EIT_Weapon UMETA(DisplayName = "Weapon"),
	EIT_Shield UMETA(DisplayName = "Shield"),
	EIT_Helmet UMETA(DisplayName = "Helmet"),
	EIT_Armor UMETA(DisplayName = "Armor"),
	EIT_Bottom UMETA(DisplayName = "Bottom"),
	EIT_ETC UMETA(DisplayName = "ETC"),
	EIT_MAX UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class EItemEquipmentType : uint8
{
	EIT_NONE UMETA(DisplayName = "None"),
	EIT_RightHand UMETA(DisplayName = "Right"),
	EIT_LeftHand UMETA(DisplayName = "Left"),
    EIT_Head UMETA(DisplayName = "Head"),
	EIT_Upper UMETA(DisplayName = "Upper"),
	EIT_Bottom UMETA(DisplayName = "Bottom"),
	EIT_Potion UMETA(DisplayName = "Potion"),
	EIT_Back UMETA(DisplayName = "Back"),
	EIt_MAX UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EItemClass : uint8
{
	EIC_NONE UMETA(DisplayName = "None"),
	EIC_Normal UMETA(DisplayName = "Normal"),
	EIC_Rare UMETA(DisplayName = "Rare"),
	EIC_Unique UMETA(DisplayName = "Unique"),
	EIC_Legend UMETA(DisplayName = "Legend"),
	EIC_MAX UMETA(DisplayName = "Max")
};

USTRUCT(BlueprintType)
struct FInventoryItemData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FInventoryItemData()
	{
		eItemClass = EItemClass::EIC_Normal;
		bIsCount = false;
		Count = 0;
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	class UTexture2D* ItemTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	bool bIsCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 Count;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString ItemDesc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	EItemType ItemType;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName EquipSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TMap<FString, float> mapAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* UseSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* EquipSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	EItemClass eItemClass;

};
