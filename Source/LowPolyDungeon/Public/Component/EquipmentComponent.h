// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Equipable.h"
#include "Enums/ItemEnums.h"
#include "EquipmentComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnEquipItemDelegate,  class AItemBase*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipItemDelegate, class AItemBase*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	EItemEquipmentType ConvertToEquipType(EItemType type);

	/* 오른손에 장착중인 아이템을 등에 장착할 것인가? 손에 장착할 것인가?*/
	UFUNCTION(BlueprintCallable)
	void SwapEquippedItemType(class USkeletalMeshComponent* mesh);

	UFUNCTION(BlueprintCallable)
	void EquipDefaultItem(class USkeletalMeshComponent* mesh);

	UFUNCTION(BlueprintCallable)
	void UseSelectedItem(int32 index);

	UFUNCTION(BlueprintCallable)
	void UseItem(EItemEquipmentType type, int32 index);

	UFUNCTION(BlueprintCallable)
	void CreateItemAndEquip(class USkeletalMeshComponent* mesh, TSubclassOf<class AItemBase> itemClass);

	UFUNCTION(BlueprintCallable)
	void Equip(class USkeletalMeshComponent* mesh, AItemBase* item, bool onSound);

	UFUNCTION(BlueprintCallable)
	void Unequip(USkeletalMeshComponent* mesh, EItemEquipmentType type);

	UFUNCTION(BlueprintPure)
	AItemBase* GetEquippedItem(EItemEquipmentType type);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TMap<EItemEquipmentType, AItemBase*> mapEquippedItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TMap<EItemEquipmentType, TSubclassOf<AItemBase>> mapDefaultItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | Sound")
	USoundCue* pullWeaponSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | Sound")
	USoundCue* pushWeaponSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	AItemBase* SelectedItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName BackSocket;

	FOnEquipItemDelegate OnEquipDelegate;
	FOnUnEquipItemDelegate OnUnequipDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class ALowpolyCharacter* character;


	
};
