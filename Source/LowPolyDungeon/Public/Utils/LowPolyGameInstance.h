// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Enums/ItemEnums.h"
#include "Enums/CharacterEnums.h"
#include "LowPolyGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API ULowPolyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ULowPolyGameInstance();

	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<int32, FInventoryItemData> mapItemData;


public:
	UFUNCTION(BlueprintCallable)
	FInventoryItemData GetItemData(const int32 itemID);



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	class UDataTable* itemData;







};
