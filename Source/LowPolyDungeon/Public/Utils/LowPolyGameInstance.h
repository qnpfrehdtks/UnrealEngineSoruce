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
	/* 아이템 정보를 가지고 있는 Instance, 유니티의 싱글톤 Manager 처럼 사용중*/
	UFUNCTION(BlueprintCallable)
	FInventoryItemData GetItemData(const int32 itemID);



protected:
	/* 아이템의 데이터를 담은 DataTable 에디터에서 설정. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	class UDataTable* itemData;







};
