// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SpawnActor.h"
#include "Actor/ItemBase.h"
#include "Actor/AICharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h" 

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Sound/SoundCue.h"

// Custom include 

#include "Component/StatComponent.h"
#include "Component/FSMComponent.h"
#include "Component/TargetingComponent.h"
#include "Component/EquipmentComponent.h"
#include "Component/InteractComponent.h"
#include "Component/InventoryComponent.h"

#include "Widget/InventoryUserWidget.h"

#include "Utils/LowpolyPlayerContorller.h"
#include "Utils/LowPolyGameInstance.h"

#include "State/IdleState.h"
#include "State/CombatState.h"


#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

#include "Actor/ItemBase.h"
#include "Components/WidgetComponent.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnCollision"));
	SetRootComponent(SpawnBoxCollider);

	SpawnBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnSphere"));
	SpawnBoxComponent->SetupAttachment(SpawnBoxCollider);

	SpawnBoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	SpawnBoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SpawnBoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	SpawnBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnActor::OnHitCollisionToItem);
}

void ASpawnActor::OnHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
	{
		return;
	}

	ALowpolyCharacter* character = Cast<ALowpolyCharacter>(OtherActor);

	if (character == nullptr)
	{
		return;
	}

	ACharacter* playerChracter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (character == playerChracter)
	{
		OnSpawnActor();
	}
}


void ASpawnActor::OnSpawnActor()
{
	if (bIsSpawned)
	{
		return;
	}

	if (SpawnSoundCue)
	{
		audioComponent = UGameplayStatics::SpawnSound2D(this, SpawnSoundCue, 1.0f);
		audioComponent->Play();
	}
		//UGameplayStatics::PlaySound2D(GetWorld(), SpawnSoundCue, 1.0f);

	for (int32 i = 0; i < SpawnCount; i++)
	{
		FActorSpawnParameters param;
		param.Owner = this;

		FVector randPos = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBoxComponent->GetComponentLocation(), SpawnBoxComponent->GetScaledBoxExtent());

		FRotator rot = UKismetMathLibrary::MakeRotator(0, 0, FMath::RandRange(0, 360));
		AAICharacterBase* newActor = GetWorld()->SpawnActor<AAICharacterBase>(SpawnActor, randPos, rot, param);


		if (newActor == nullptr)
		{
			return;
		}

		if(SpawnParticle)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, randPos, rot, true);

		if (newActor->StatComponent != nullptr)
			newActor->StatComponent->OnHPZeroDelegate.AddLambda(
				[this]()
				{
					if (audioComponent)
					{
						audioComponent->StopDelayed(2.0f);
					}
				}
		);
	}

	bIsSpawned = true;

}

