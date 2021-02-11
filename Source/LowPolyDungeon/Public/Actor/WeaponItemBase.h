// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/ItemBase.h"
#include "WeaponItemBase.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName TopSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName BottomSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float Radius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class USoundCue* AttackSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* HitEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* TrailEffect;

	UFUNCTION(BlueprintCallable)
	bool OnCheckHit(class UStateBase* state);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float AttackPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float CurrentCombo;

	UFUNCTION()
	void ResetTimer();

	//void TimeReset();

	FOnHitDelegate OnHitDelegate;

	FTimerHandle timerHandler;

	// ------------ interface --------------
	virtual void UseItem_Implementation(int32 index) override;


};
