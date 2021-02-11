// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPDamageDelegate, float);
DECLARE_MULTICAST_DELEGATE(FOnStaminaZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnStaminaDamageDelegate);
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

	UFUNCTION(BlueprintCallable)
	void DamageHealth(float damage);

	UFUNCTION(BlueprintCallable)
	float GetHealthRatio();

	UFUNCTION(BlueprintCallable)
	void DamageStamina(float stamina);

	UFUNCTION(BlueprintCallable)
	float GetStaminaRatio();

	UFUNCTION(BlueprintCallable)
	void RegenerateHealth(float health);

	UFUNCTION(BlueprintCallable)
	void RegenerateStamina(float stamina);

	UFUNCTION(BlueprintCallable)
	bool CheckHPZero();

	UFUNCTION(BlueprintCallable)
	bool CheckStaminaZero();

	FOnHPZeroDelegate OnHPZeroDelegate;
	FOnHPDamageDelegate OnHPDamageDelegate;

	FOnStaminaZeroDelegate OnStaminaZeroDelegate;
	FOnStamina30PercentDelegate OnStamina30PercentDelegate;
	FOnStaminaDamageDelegate OnStaminaDamageDelegate;
};
