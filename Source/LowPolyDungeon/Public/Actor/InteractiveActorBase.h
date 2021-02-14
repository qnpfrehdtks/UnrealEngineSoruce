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

	/* IInteractive �������̽� ���� */
	virtual bool OnStartInteractive_Implementation(AActor* actor) override;


	/* �������Ʈ�� �����ؼ� ����Ѵ�. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartInteractiveEvent(class AItemBase* item);

	/* ���ͷ�Ʈ �� ����*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* InteractSound;

	/* ���ͷ�Ʈ ���н� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* InteractFailSound;

	/* ���ͷ�Ʈ �� �浹 ���Ǿ� ũ�� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class USphereComponent* SphereComponent;

	/* �ִϸ��̼��� �ִ� �޽� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* Mesh;

	/* ����ƽ �޽� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;

	/* ��ȣ�ۿ�� ����� ��Ʈ�� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "String")
	FString InteractString;

	/* ���ͷ�Ʈ Ÿ����? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	EInteractiveType interactType;
};
