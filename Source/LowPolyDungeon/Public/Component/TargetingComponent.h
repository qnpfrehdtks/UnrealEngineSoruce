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

	UFUNCTION(BlueprintCallable)
	void FindLockOnTarget(FVector start, FRotator dir);

	UFUNCTION(BlueprintCallable)
	void ChangeLockOnTarget(FVector start, FRotator dir);

	UFUNCTION(BlueprintCallable)
	void UnLockTarget();

	UFUNCTION(BlueprintCallable)
	void UnLockTargetByMyself();

	UFUNCTION(BlueprintCallable)
	bool LockTarget(AActor* target);

	UFUNCTION(BlueprintCallable)
	void AddTargetingMEObject(AActor* target);

	UFUNCTION(BlueprintCallable)
	void RemoveTargetingMeObject(AActor* target);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float TargetingRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float FindTargetingPeriod;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TArray<TEnumAsByte< EObjectTypeQuery>> arrayTargetObjectType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TArray<AActor*> ActorsToIgnore;

	FOnTargeting OnTargetingDelegate;

	UFUNCTION(BlueprintCallable)
	void OnTargetUpdateRotation(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void OnTargetUpdateCamera(float DeltaTime);




	
};
