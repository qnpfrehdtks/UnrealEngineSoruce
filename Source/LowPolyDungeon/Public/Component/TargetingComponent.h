// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Targetable.h"
#include "TargetingComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTargeting);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> arrTargeting;
public:	
	UPROPERTY(VisibleAnywhere , BlueprintReadWrite, Category = "Targeting")
	AActor* TargetObject;

	/* Ÿ���� �˻� */
	UFUNCTION(BlueprintCallable)
	void FindLockOnTarget(FVector start, FRotator dir);

	/* Ÿ���� ���� */
	UFUNCTION(BlueprintCallable)
	void ChangeLockOnTarget(FVector start, FRotator dir);

	/* Ÿ�� ������ Ǭ��. */
	UFUNCTION(BlueprintCallable)
	void UnLockTarget();

	/* ������ Ÿ���� �� �ڽ��� Ǭ��. */
	UFUNCTION(BlueprintCallable)
	void UnLockTargetByMyself();

	/* Ÿ���� �� �Ѵ�. */
	UFUNCTION(BlueprintCallable)
	bool LockTarget(AActor* target);

	/* Ÿ���ϰ� �ִ� ����� ����ִ´�. ������ ������ Ÿ������ Ǯ�� ���� ����*/
	UFUNCTION(BlueprintCallable)
	void AddTargetingMEObject(AActor* target);

	/* �� Ÿ�� �ϰ� �ִ� ���͸� �����Ѵ�. */
	UFUNCTION(BlueprintCallable)
	void RemoveTargetingMeObject(AActor* target);

	/* Ÿ�� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float TargetingRange;

	/* Ÿ���� �ð����� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float FindTargetingPeriod;

	/* Ÿ������ ����� �ݸ��� Ÿ�� ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TArray<TEnumAsByte< EObjectTypeQuery>> arrayTargetObjectType;

	/* ������ Ÿ���� ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TArray<AActor*> ActorsToIgnore;

	/* */
	FOnTargeting OnTargetingDelegate;

	/* Ÿ���� ��, ĳ���� �����̼� ������Ʈ */
	UFUNCTION(BlueprintCallable)
	void OnTargetUpdateRotation(float DeltaTime);


	/* Ÿ���� ��, ī�޶� �����̼� ������Ʈ */
	UFUNCTION(BlueprintCallable)
	void OnTargetUpdateCamera(float DeltaTime);




	
};
