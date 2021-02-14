// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/ItemBase.h"
#include "WeaponItemBase.generated.h"

/* 무기 아이템이 액터와 히트시 발생시키는 함수입니다./ */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHitDelegate, AActor*, AActor*);

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API AWeaponItemBase : public AItemBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	

private:
	static const FString attackAttriName;
	static const FString attackRangeName;

public:
	AWeaponItemBase();

	/* 무기의 탑 소켓 네임 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName TopSocketName;

	/* 무기의 바탐 소켓 네임 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName BottomSocketName;

	/* 무기의 공격 반지름 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float Radius;

	/* 공격시 사운드 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class USoundCue* AttackSound;

	/* 히트 이펙트 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* HitEffect;

	/* 트레일 이펙트 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* TrailEffect;

	/* 공격이 히트했는지 판별합니다. */
	UFUNCTION(BlueprintCallable)
	bool OnCheckHit(class UStateBase* state);

	/* 공격력 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float AttackPoint;

	/* 현재 콤보 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float CurrentCombo;

	/* 리셋 */
	UFUNCTION()
	void ResetTimer();

	//void TimeReset();

	FOnHitDelegate OnHitDelegate;

	FTimerHandle timerHandler;

	// ------------ interface --------------
	virtual void UseItem_Implementation(int32 index) override;


};
