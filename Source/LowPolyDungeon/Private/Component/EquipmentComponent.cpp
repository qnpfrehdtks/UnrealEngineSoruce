// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EquipmentComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h" 

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Sound/SoundCue.h"

// Custom include 

#include "Component/StatComponent.h"
#include "Component/FSMComponent.h"
#include "Component/TargetingComponent.h"

#include "State/IdleState.h"
#include "State/CombatState.h"


#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

#include "Actor/ItemBase.h"
#include "Actor/LowpolyCharacter.h"

#include "Utils/LowPolyGameInstance.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	BackSocket = TEXT("BackSocket");
	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<ALowpolyCharacter>(GetOwner());
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::EquipDefaultItem(USkeletalMeshComponent* mesh)
{
	// ���� ���۽� ������ ������ ����Դϴ�.
	auto item = mapDefaultItem.Find(EItemEquipmentType::EIT_Bottom);
	if(item != nullptr) CreateItemAndEquip(mesh, *item);

	item = mapDefaultItem.Find(EItemEquipmentType::EIT_Head);
	if (item != nullptr) CreateItemAndEquip(mesh, *item);

	item = mapDefaultItem.Find(EItemEquipmentType::EIT_LeftHand);
	if (item != nullptr) CreateItemAndEquip(mesh, *item);

	item = mapDefaultItem.Find(EItemEquipmentType::EIT_Potion);
	if (item != nullptr) CreateItemAndEquip(mesh, *item);

	item = mapDefaultItem.Find(EItemEquipmentType::EIT_RightHand);
	if (item != nullptr)CreateItemAndEquip(mesh, *item);

	item = mapDefaultItem.Find(EItemEquipmentType::EIT_Upper);
	if (item != nullptr) CreateItemAndEquip(mesh, *item);

	SelectedItem = GetEquippedItem(EItemEquipmentType::EIT_Potion);
}

void UEquipmentComponent::UseSelectedItem( int32 index)
{
	if (SelectedItem == nullptr)
	{
		SelectedItem = GetEquippedItem(EItemEquipmentType::EIT_Potion);
	}

	if (SelectedItem != nullptr)
	{
		SelectedItem->UseItem_Implementation(index);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not have a Item Key "));
	}
}

void UEquipmentComponent::UseItem(EItemEquipmentType type,int32 index)
{
	AItemBase* item = GetEquippedItem(type);

	if (item != nullptr)
	{
		item->UseItem_Implementation(index);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not have a Item Key "));
	}
}

EItemEquipmentType UEquipmentComponent::ConvertToEquipType(EItemType type)
{
	// ������ Ÿ�Կ����� ���� ���� enum ����
	switch (type)
	{
	case EItemType::EIT_Weapon:
		return EItemEquipmentType::EIT_RightHand;
	case EItemType::EIT_Shield:
		return EItemEquipmentType::EIT_LeftHand;
	case EItemType::EIT_Helmet:
		return EItemEquipmentType::EIT_Head;
	case EItemType::EIT_Armor:
		return EItemEquipmentType::EIT_Upper;
	case EItemType::EIT_Bottom:
		return EItemEquipmentType::EIT_Bottom;
	case EItemType::EIT_ETC:
		return EItemEquipmentType::EIT_Potion;
	default:
		return EItemEquipmentType::EIT_NONE;
	}

	return EItemEquipmentType();
}


void UEquipmentComponent::SwapEquippedItemType(USkeletalMeshComponent* mesh)
{
	auto equippedWeapon = GetEquippedItem(EItemEquipmentType::EIT_RightHand);
	auto backWeapon = GetEquippedItem(EItemEquipmentType::EIT_Back);

	/* �������� � �ٽ� �����ҽ�*/
	if (equippedWeapon != nullptr && backWeapon == nullptr)
	{
		UGameplayStatics::PlaySound2D(this, pushWeaponSound);

		/* IEquipable �������̽� Ȱ�� */
		IEquipable::Execute_OnEquip_EquipType(equippedWeapon, mesh, BackSocket);
		mapEquippedItem.Add(EItemEquipmentType::EIT_Back, equippedWeapon);
		mapEquippedItem.Remove(EItemEquipmentType::EIT_RightHand);
	}
	/* �������� ���������� �ٽ� ������ �ÿ�*/
	else if (equippedWeapon == nullptr &&  backWeapon != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, pullWeaponSound);

		/* IEquipable �������̽� Ȱ�� */
		IEquipable::Execute_OnEquip(backWeapon, mesh);
		mapEquippedItem.Add(EItemEquipmentType::EIT_RightHand, backWeapon);
		mapEquippedItem.Remove(EItemEquipmentType::EIT_Back);
	}
}


void UEquipmentComponent::CreateItemAndEquip( USkeletalMeshComponent* mesh, TSubclassOf<AItemBase> itemClass)
{
	FActorSpawnParameters prams;
	prams.Owner = GetOwner();

	// �������� �����ϰ�
	AItemBase* newItem = GetWorld()->SpawnActor<AItemBase>(itemClass, FVector::ZeroVector, FRotator::ZeroRotator, prams);
	
	if (character != nullptr && newItem )
	{
		if (character->IsPlayerControlled())
		{
			// �κ��丮�� ����ְ�
			character->InsertToInventory(newItem);
		}
	}

	//�����Ѵ�.
	Equip(mesh, newItem, false);
}

void UEquipmentComponent::Equip(USkeletalMeshComponent* mesh, AItemBase* item, bool onSound)
{
	/* GameInstacne  �� ���� �������� ������ �����´�. */
	ULowPolyGameInstance* instance = Cast<ULowPolyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	FInventoryItemData itemData;

	if (instance != nullptr)
	{
		itemData = instance->GetItemData(item->GetItemID());
	}
	/* �������� ���ٸ� return */
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is nullptr"));
		return;
	}

	EItemEquipmentType equippedItemType = ConvertToEquipType(itemData.ItemType);

	/*  �����ۿ� �´� �������� �����Ѵ�. */
	if (item && equippedItemType != EItemEquipmentType::EIT_NONE)
	{
		Unequip(mesh, equippedItemType);

		OnEquipDelegate.Broadcast(item);
		IEquipable::Execute_OnEquip(item, mesh);

		if (onSound)
		{
			item->PlayEquipItemSound();
		}

		mapEquippedItem.Add(equippedItemType, item);
	}
}

void UEquipmentComponent::Unequip(USkeletalMeshComponent* mesh, EItemEquipmentType type)
{
	/* � �ִ� �������� ��� �ѹ� ���� */
	if (type == EItemEquipmentType::EIT_RightHand)
	{
		auto backWeapon = GetEquippedItem(EItemEquipmentType::EIT_Back);
		auto rightWeapon = GetEquippedItem(EItemEquipmentType::EIT_RightHand);
		
		if (backWeapon != nullptr && rightWeapon == nullptr)
		{
			SwapEquippedItemType(mesh);
		}
	}

	/* ������ �����ۿ��� ������ ������ �������� */
	AItemBase* oldItem = GetEquippedItem(type);

	/* �����Ѵ�. */
	if (oldItem != nullptr)
	{
		OnUnequipDelegate.Broadcast(oldItem);
		mapEquippedItem.Remove(type);
		IEquipable::Execute_OnDetach(oldItem);
	}
}

AItemBase* UEquipmentComponent::GetEquippedItem(EItemEquipmentType type)
{
	auto item = mapEquippedItem.Find(type);
	return item == nullptr ? nullptr : *item;
}



