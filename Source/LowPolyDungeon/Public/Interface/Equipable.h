// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/ItemEnums.h"
#include "Equipable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquipable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOWPOLYDUNGEON_API IEquipable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEquipable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equip")
	void OnEquip(class USkeletalMeshComponent* mesh);
	virtual void OnEquip_Implementation(class USkeletalMeshComponent* mesh);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equip")
	void OnEquip_EquipType(class USkeletalMeshComponent* mesh, FName SocketName);
	virtual void OnEquip_EquipType_Implementation(class USkeletalMeshComponent* mesh, FName SocketName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equip")
	void OnDetach();
	virtual void OnDetach_Implementation();
};
