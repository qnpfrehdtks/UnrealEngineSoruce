// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

/* 적을 스폰해주는 액터 */
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

	/* 스폰할 액터 타입 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	TSubclassOf<class ALowpolyCharacter> SpawnActor;

	/* 스폰 갯수 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	int32 SpawnCount;

	/* 스폰 할 트리거 박스 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnActor")
	UBoxComponent* SpawnBoxComponent;

	/* 스폰시 사운드 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	class USoundCue* SpawnSoundCue;

	/* 스폰할 위치의 콜리더 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnActor")
	TArray<class AActor*> ListBoxCollider;

	/* 스폰시 파티클 재생*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	UParticleSystem* SpawnParticle;

	/* 이미 스폰되었나?*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnActor")
	bool bIsSpawned;


	/* 적을 스폰합니다. */
	UFUNCTION()
	void OnSpawnActor();

	/* 스폰시 발생 이벤트 */
	UFUNCTION()
	void OnHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
