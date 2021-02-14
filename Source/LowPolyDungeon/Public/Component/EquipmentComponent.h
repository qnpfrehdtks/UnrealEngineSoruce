// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Equipable.h"
#include "Enums/ItemEnums.h"
#include "EquipmentComponent.generated.h"

// 아이템 탈착시 델리게이트 
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnEquipItemDelegate,  class AItemBase*);

// 아이템 착용시 델리게이트
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

	// 디폴트 아이템을 장착시킨다.
	UFUNCTION(BlueprintCallable)
	void EquipDefaultItem(class USkeletalMeshComponent* mesh);

	// 선택된 아이템을 사용한다.
	UFUNCTION(BlueprintCallable)
	void UseSelectedItem(int32 index);

	// 아이템을 사용한다.
	UFUNCTION(BlueprintCallable)
	void UseItem(EItemEquipmentType type, int32 index);

	// 아이템 메쉬를 생성하고 본에 장착하도록 한다.
	UFUNCTION(BlueprintCallable)
	void CreateItemAndEquip(class USkeletalMeshComponent* mesh, TSubclassOf<class AItemBase> itemClass);

	// 해당 아이템을 매쉬를 본에 장착한다/
	UFUNCTION(BlueprintCallable)
	void Equip(class USkeletalMeshComponent* mesh, AItemBase* item, bool onSound);

	// 해당 아이템을 해제한다.
	UFUNCTION(BlueprintCallable)
	void Unequip(USkeletalMeshComponent* mesh, EItemEquipmentType type);

	// 장착된 아이템 정보를 가져온다./
	UFUNCTION(BlueprintPure)
	AItemBase* GetEquippedItem(EItemEquipmentType type);

	// 장착하고 있는 아이템의 map
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TMap<EItemEquipmentType, AItemBase*> mapEquippedItem;

	// 디폴트로 착용할 아이템 map
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TMap<EItemEquipmentType, TSubclassOf<AItemBase>> mapDefaultItem;

	// 무기 탈착시 사운드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | Sound")
	USoundCue* pullWeaponSound;

	// 무기 장착시 사운드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | Sound")
	USoundCue* pushWeaponSound;

	// 현재 선택된 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	AItemBase* SelectedItem;

	// 등 뒤에 무기를 놓을 본 소켓의 이름
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName BackSocket;

	FOnEquipItemDelegate OnEquipDelegate;
	FOnUnEquipItemDelegate OnUnequipDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class ALowpolyCharacter* character;


	
};
