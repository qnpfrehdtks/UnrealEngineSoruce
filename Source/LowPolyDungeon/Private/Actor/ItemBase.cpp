// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ItemBase.h"

#include "Camera/CameraComponent.h"
#include "Enums/CharacterEnums.h"


#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h" 

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

#include "Component/FSMComponent.h"
#include "Actor/LowPolyCharacter.h"
#include "DrawDebugHelpers.h"

#include "Particles/ParticleSystemComponent.h"

#include "Utils/LowPolyGameInstance.h"

#include "Enums/ItemEnums.h"

#include "Sound/SoundCue.h"

// Sets default values
AItemBase::AItemBase()
{

	BoxComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Box"));
	SetRootComponent(BoxComponent);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ItemMesh->SetupAttachment(GetRootComponent());

	StaticItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticItemMesh->SetupAttachment(GetRootComponent());

	StaticItemMesh->SetRelativeLocation(FVector::ZeroVector);
	
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	isEquipped = false;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	StaticItemMesh->SetRelativeLocation(FVector::ZeroVector);
	uniqueItemID = GetUniqueID();
	SetVisibleItemVisible(false);
	InitializeItemDate();
}


void AItemBase::InitializeItemDate()
{
	ULowPolyGameInstance* instacne = Cast<ULowPolyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (instacne == nullptr)
	{
		return;
	}

	FInventoryItemData data = instacne->GetItemData(ItemID);

	if (data.ItemID != ItemID)
	{
		return;
	}

	itemData = data;
}

void AItemBase::UseItem_Implementation(int32 index)
{
	if (IsStackCount() && GetCount() <= 0)
	{
		return;
	}
	else if (IsStackCount() && GetCount() > 0)
	{
		itemData.Count--;

		if (GetCount() <= 0)
		{
			itemData.Count = 0;
		}
	}

	if (itemData.UseSoundCue)
	{
		UGameplayStatics::PlaySound2D(this, itemData.UseSoundCue);
	}

	ALowpolyCharacter* character  = Cast<ALowpolyCharacter>(GetOwner());
	character->FSM->PushState(ECharacterState::ECS_Drink);

	return;

}

void AItemBase::AttachToMesh_ByName(USkeletalMeshComponent* mesh, FName SocketName)
{
	AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	SetOwner(mesh->GetOwner());

	SetVisibleItemVisible(true);

	isEquipped = true;
}

void AItemBase::AttachToMesh(USkeletalMeshComponent* mesh)
{
	AttachToMesh_ByName(mesh, GetSocketName());
}

void AItemBase::PlayEquipItemSound()
{
	if (itemData.EquipSoundCue)
	{
		UGameplayStatics::PlaySound2D(this, itemData.EquipSoundCue);
	}
}

void AItemBase::SetVisibleItemVisible(bool active)
{
	if(ItemMesh)
		ItemMesh->SetVisibility(active);

	if (StaticItemMesh)
		StaticItemMesh->SetVisibility(active);
}

void AItemBase::OnEquip_Implementation( USkeletalMeshComponent* mesh)
{
	AttachToMesh_ByName(mesh, GetSocketName());
}

void AItemBase::OnEquip_EquipType_Implementation(USkeletalMeshComponent* mesh, FName SocketName)
{
	AttachToMesh_ByName(mesh, SocketName);
}

void AItemBase::OnDetach_Implementation()
{
	isEquipped = false;
	SetVisibleItemVisible(false);
}

