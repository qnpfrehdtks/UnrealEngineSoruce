// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SoulItem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Actor/LowpolyCharacter.h"

#include "Actor/ItemBase.h"

#include "Engine/World.h"

ASoulItem::ASoulItem()
{
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParicleComp"));
	ParticleComponent->SetupAttachment(GetRootComponent());
	ParticleComponent->SetRelativeScale3D(FVector(0.35f, 0.35f, 0.35f));
}

void ASoulItem::BeginPlay()
{

}

bool ASoulItem::OnStartInteractive_Implementation(AActor* actor)
{
	Super::OnStartInteractive_Implementation(actor);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Iteract222222 %s"), *GetName()));

	ALowpolyCharacter* character =  Cast<ALowpolyCharacter>(actor);

	FActorSpawnParameters prams;
	prams.Owner = GetOwner();

	/* 인터렉트 시작시 자신에게 등록된 아이템 정보를 스폰하고, 캐릭터의 인벤토리에 전달한다. */
	AItemBase* newItem = GetWorld()->SpawnActor<AItemBase>(soulItemClass, FVector::ZeroVector, FRotator::ZeroRotator, prams);

	if (character != nullptr && soulItemClass != nullptr)
	{
		/* 아이템 생성 루틴 */
		character->InsertToInventory(newItem);
		newItem->InitializeItemDate();
		OnStartInteractiveEvent(newItem);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interacr Fail!!!"));
	}

	/* 파티클 종료 ㅡ 비활성화 */
	Mesh->SetVisibility(false);
	ParticleComponent->Deactivate();

	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->Deactivate();

	auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InteractParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	//particle->SetRelativeScale3D(FVector(1.00f, 0.35f, 0.35f));

	return true;
}

