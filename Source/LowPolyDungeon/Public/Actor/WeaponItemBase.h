// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/ItemBase.h"
#include "WeaponItemBase.generated.h"

/* ���� �������� ���Ϳ� ��Ʈ�� �߻���Ű�� �Լ��Դϴ�./ */
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

	/* ������ ž ���� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName TopSocketName;

	/* ������ ��Ž ���� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName BottomSocketName;

	/* ������ ���� ������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float Radius;

	/* ���ݽ� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class USoundCue* AttackSound;

	/* ��Ʈ ����Ʈ */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* HitEffect;

	/* Ʈ���� ����Ʈ */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* TrailEffect;

	/* ������ ��Ʈ�ߴ��� �Ǻ��մϴ�. */
	UFUNCTION(BlueprintCallable)
	bool OnCheckHit(class UStateBase* state);

	/* ���ݷ� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float AttackPoint;

	/* ���� �޺� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float CurrentCombo;

	/* ���� */
	UFUNCTION()
	void ResetTimer();

	//void TimeReset();

	FOnHitDelegate OnHitDelegate;

	FTimerHandle timerHandler;

	// ------------ interface --------------
	virtual void UseItem_Implementation(int32 index) override;


};
