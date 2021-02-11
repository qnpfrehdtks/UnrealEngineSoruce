// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/LowPolyGameInstance.h"
#include "Actor/ItemBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Actor/LowpolyCharacter.h"
#include "..\..\Public\Actor\AICharacterBase.h"
#include "Sound/SoundCue.h"

ULowPolyGameInstance::ULowPolyGameInstance()
{

}

void ULowPolyGameInstance::Init()
{
	Super::Init();

	TArray<FInventoryItemData*> arrayData;
	itemData->GetAllRows(FString(""), arrayData);
	for (auto& data : arrayData)
	{
		if (data == nullptr) continue;
		if (mapItemData.Contains(data->ItemID) == false)
		{
			mapItemData.Add(data->ItemID, *data);
		}
	}

}

FInventoryItemData ULowPolyGameInstance::GetItemData(const int32 itemID)
{
	auto item = mapItemData.Find(itemID);
	return item == nullptr ? FInventoryItemData() : *item;
}




