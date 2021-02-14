// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Equipable.h"
#include "Enums/ItemEnums.h"
#include "EquipmentComponent.generated.h"

// ������ Ż���� ��������Ʈ 
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnEquipItemDelegate,  class AItemBase*);

// ������ ����� ��������Ʈ
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

	/* �����տ� �������� �������� � ������ ���ΰ�? �տ� ������ ���ΰ�?*/
	UFUNCTION(BlueprintCallable)
	void SwapEquippedItemType(class USkeletalMeshComponent* mesh);

	// ����Ʈ �������� ������Ų��.
	UFUNCTION(BlueprintCallable)
	void EquipDefaultItem(class USkeletalMeshComponent* mesh);

	// ���õ� �������� ����Ѵ�.
	UFUNCTION(BlueprintCallable)
	void UseSelectedItem(int32 index);

	// �������� ����Ѵ�.
	UFUNCTION(BlueprintCallable)
	void UseItem(EItemEquipmentType type, int32 index);

	// ������ �޽��� �����ϰ� ���� �����ϵ��� �Ѵ�.
	UFUNCTION(BlueprintCallable)
	void CreateItemAndEquip(class USkeletalMeshComponent* mesh, TSubclassOf<class AItemBase> itemClass);

	// �ش� �������� �Ž��� ���� �����Ѵ�/
	UFUNCTION(BlueprintCallable)
	void Equip(class USkeletalMeshComponent* mesh, AItemBase* item, bool onSound);

	// �ش� �������� �����Ѵ�.
	UFUNCTION(BlueprintCallable)
	void Unequip(USkeletalMeshComponent* mesh, EItemEquipmentType type);

	// ������ ������ ������ �����´�./
	UFUNCTION(BlueprintPure)
	AItemBase* GetEquippedItem(EItemEquipmentType type);

	// �����ϰ� �ִ� �������� map
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TMap<EItemEquipmentType, AItemBase*> mapEquippedItem;

	// ����Ʈ�� ������ ������ map
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TMap<EItemEquipmentType, TSubclassOf<AItemBase>> mapDefaultItem;

	// ���� Ż���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | Sound")
	USoundCue* pullWeaponSound;

	// ���� ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | Sound")
	USoundCue* pushWeaponSound;

	// ���� ���õ� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	AItemBase* SelectedItem;

	// �� �ڿ� ���⸦ ���� �� ������ �̸�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName BackSocket;

	FOnEquipItemDelegate OnEquipDelegate;
	FOnUnEquipItemDelegate OnUnequipDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class ALowpolyCharacter* character;


	
};
