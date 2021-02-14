// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

// HP���ΰ� �ɽ� ����Ǵ� ��Ƽĳ��Ʈ ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);

// HP Damage�� ���� �� ����Ǵ� ��������Ʈ
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPDamageDelegate, float);

// ���¹̳��� ���ΰ� �� �� ����Ǵ� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnStaminaZeroDelegate);

// ���¹̳��� ���ظ� ���� �� ����Ǵ� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnStaminaDamageDelegate);

// ���¹̳��� 30���� ���ϰ� �� �� ����Ǵ� ��������Ʈ
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

	// ������ ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void DamageHealth(float damage);

	// ���� : ����ü�� / �ִ�ü�� 
	UFUNCTION(BlueprintCallable)
	float GetHealthRatio();

	// ���¹̳� ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void DamageStamina(float stamina);

	// ���� : ���� ���¹̳� / �ִ� ���¹̳�
	UFUNCTION(BlueprintCallable)
	float GetStaminaRatio();

	// ü�� ���.
	UFUNCTION(BlueprintCallable)
	void RegenerateHealth(float health);

	// ���¹̳� ���
	UFUNCTION(BlueprintCallable)
	void RegenerateStamina(float stamina);

	// ü���� 0���� üũ
	UFUNCTION(BlueprintCallable)
	bool CheckHPZero();

	// ���¹̳��� 0���� �n,
	UFUNCTION(BlueprintCallable)
	bool CheckStaminaZero();

	FOnHPZeroDelegate OnHPZeroDelegate;
	FOnHPDamageDelegate OnHPDamageDelegate;
	FOnStaminaZeroDelegate OnStaminaZeroDelegate;
	FOnStamina30PercentDelegate OnStamina30PercentDelegate;
	FOnStaminaDamageDelegate OnStaminaDamageDelegate;
};
