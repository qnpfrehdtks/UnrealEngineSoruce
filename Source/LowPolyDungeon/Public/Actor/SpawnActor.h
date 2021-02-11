// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class LOWPOLYDUNGEON_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "audio")
	class UAudioComponent* audioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnActor")
	class UBoxComponent* SpawnBoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	TSubclassOf<class ALowpolyCharacter> SpawnActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	int32 SpawnCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnActor")
	UBoxComponent* SpawnBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	class USoundCue* SpawnSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnActor")
	TArray<class AActor*> ListBoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	UParticleSystem* SpawnParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	bool bIsSpawned;



	UFUNCTION()
	void OnSpawnActor();

	UFUNCTION()
	void OnHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
