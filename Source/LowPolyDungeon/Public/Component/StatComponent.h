// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

// HP제로가 될시 실행되는 멀티캐스트 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);

// HP Damage를 입을 시 실행되는 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPDamageDelegate, float);

// 스태미나가 제로가 될 시 실행되는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnStaminaZeroDelegate);

// 스태미나가 피해를 입을 시 실행되는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnStaminaDamageDelegate);

// 스태미나가 30프로 이하가 될 시 실행되는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnStamina30PercentDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat")
	float CurrentStamina;

	// 데미지 피해 함수
	UFUNCTION(BlueprintCallable)
	void DamageHealth(float damage);

	// 리턴 : 현재체력 / 최대체력 
	UFUNCTION(BlueprintCallable)
	float GetHealthRatio();

	// 스태미나 피해 함수
	UFUNCTION(BlueprintCallable)
	void DamageStamina(float stamina);

	// 리턴 : 현재 스태미나 / 최대 스태미나
	UFUNCTION(BlueprintCallable)
	float GetStaminaRatio();

	// 체력 재생.
	UFUNCTION(BlueprintCallable)
	void RegenerateHealth(float health);

	// 스태미나 재생
	UFUNCTION(BlueprintCallable)
	void RegenerateStamina(float stamina);

	// 체력이 0인지 체크
	UFUNCTION(BlueprintCallable)
	bool CheckHPZero();

	// 스태미나가 0인지 쳌,
	UFUNCTION(BlueprintCallable)
	bool CheckStaminaZero();

	FOnHPZeroDelegate OnHPZeroDelegate;
	FOnHPDamageDelegate OnHPDamageDelegate;
	FOnStaminaZeroDelegate OnStaminaZeroDelegate;
	FOnStamina30PercentDelegate OnStamina30PercentDelegate;
	FOnStaminaDamageDelegate OnStaminaDamageDelegate;
};
