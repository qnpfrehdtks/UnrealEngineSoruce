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

	/* 타겟팅 검색 */
	UFUNCTION(BlueprintCallable)
	void FindLockOnTarget(FVector start, FRotator dir);

	/* 타겟팅 변경 */
	UFUNCTION(BlueprintCallable)
	void ChangeLockOnTarget(FVector start, FRotator dir);

	/* 타겟 락온을 푼다. */
	UFUNCTION(BlueprintCallable)
	void UnLockTarget();

	/* 스스로 타겟팅 된 자신을 푼다. */
	UFUNCTION(BlueprintCallable)
	void UnLockTargetByMyself();

	/* 타게을 락 한다. */
	UFUNCTION(BlueprintCallable)
	bool LockTarget(AActor* target);

	/* 타겟하고 있는 대상을 집어넣는다. 이유는 스스로 타겟팅을 풀기 위해 만듦*/
	UFUNCTION(BlueprintCallable)
	void AddTargetingMEObject(AActor* target);

	/* 날 타겟 하고 있는 액터를 제거한다. */
	UFUNCTION(BlueprintCallable)
	void RemoveTargetingMeObject(AActor* target);

	/* 타겟 범위 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float TargetingRange;

	/* 타겟할 시간간격 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float FindTargetingPeriod;

	/* 타겟팅할 대상의 콜리전 타입 정의 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TArray<TEnumAsByte< EObjectTypeQuery>> arrayTargetObjectType;

	/* 무시할 타겟팅 액터 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TArray<AActor*> ActorsToIgnore;

	/* */
	FOnTargeting OnTargetingDelegate;

	/* 타겟팅 후, 캐릭터 로테이션 업데이트 */
	UFUNCTION(BlueprintCallable)
	void OnTargetUpdateRotation(float DeltaTime);


	/* 타겟팅 후, 카메라 로테이션 업데이트 */
	UFUNCTION(BlueprintCallable)
	void OnTargetUpdateCamera(float DeltaTime);




	
};
