// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactive.h"
#include "InteractiveActorBase.generated.h"

UCLASS()
class LOWPOLYDUNGEON_API AInteractiveActorBase : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* IInteractive 인터페이스 구현 */
	virtual bool OnStartInteractive_Implementation(AActor* actor) override;


	/* 블루프린트와 연계해서 사용한다. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartInteractiveEvent(class AItemBase* item);

	/* 인터렉트 시 사운드*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* InteractSound;

	/* 인터렉트 실패시 사운드 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* InteractFailSound;

	/* 인터렉트 할 충돌 스피어 크기 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class USphereComponent* SphereComponent;

	/* 애니메이션이 있는 메쉬 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* Mesh;

	/* 스태틱 메시 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;

	/* 상호작용시 출력할 스트링 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "String")
	FString InteractString;

	/* 인터렉트 타입은? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	EInteractiveType interactType;
};
