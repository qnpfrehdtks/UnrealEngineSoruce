// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/InteractiveStepWall.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Actor/LowpolyCharacter.h"
#include "..\..\Public\Actor\AICharacterBase.h"
#include "Sound/SoundCue.h"

#include "Actor/ItemBase.h"

#include "Engine/World.h"

#include "Utils/LowPolyDungeonGameModeBase.h"

AInteractiveStepWall::AInteractiveStepWall()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AInteractiveStepWall::BeginPlay()
{

}

bool AInteractiveStepWall::OnStartInteractive_Implementation(AActor* actor)
{
	TArray<AActor*> arrOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacterBase::StaticClass(), arrOutActors);

	if (arrOutActors.Num() > 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InteractFailSound, 1.0f);

		auto gameMode = UGameplayStatics::GetGameMode(GetWorld());
		ALowPolyDungeonGameModeBase * myGameMode = Cast<ALowPolyDungeonGameModeBase>(gameMode);

		if (myGameMode)
		{
			myGameMode->SetWarningText(FString::Printf(TEXT("You must hunt all your enemies to open the door.")), 5.0f);
		}

		return false;
	}

	Super::OnStartInteractive_Implementation(actor);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Iteract222222 %s"), *GetName()));

	ALowpolyCharacter* character = Cast<ALowpolyCharacter>(actor);

	FActorSpawnParameters prams;
	prams.Owner = GetOwner();

	if (character != nullptr )
	{
		/* 인터렉트 시 델리게이트 실행 */
		OnStartInteractiveEvent(nullptr);
	}
	
	/* 메시 비활성화 */
	StaticMesh->SetVisibility(false);
	Mesh->SetVisibility(false);

	/* 충돌 제거 */
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->Deactivate();

	/* 파티틀 재생. */
	auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InteractParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	UGameplayStatics::PlaySound2D(GetWorld(), InteractSound, 1.0f);

	return true;
}