// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Actor\InteractiveActorBase.h"

#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AInteractiveActorBase::AInteractiveActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractRange"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(200.0f);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereComponent);

	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AInteractiveActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractiveActorBase::OnStartInteractive_Implementation(AActor* actor)
{
	return true;
}

