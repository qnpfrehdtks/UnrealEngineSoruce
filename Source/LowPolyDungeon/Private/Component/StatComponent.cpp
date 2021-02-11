// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatComponent::DamageHealth(float damage)
{
	CurrentHealth -= damage;
	OnHPDamageDelegate.Broadcast(GetHealthRatio());
	if (CheckHPZero())
	{
		CurrentHealth = 0.0f;
		OnHPZeroDelegate.Broadcast();
	}
}

float UStatComponent::GetHealthRatio()
{
	return CurrentHealth / MaxHealth;
}

void UStatComponent::DamageStamina(float stamina)
{
	CurrentStamina -= stamina;
	OnStaminaDamageDelegate.Broadcast();

	if (CheckStaminaZero())
	{
		CurrentStamina = 0.0f;
		OnStaminaZeroDelegate.Broadcast();
	}
}

float UStatComponent::GetStaminaRatio()
{
	return CurrentStamina / MaxStamina;
}

void UStatComponent::RegenerateHealth(float health)
{
	CurrentHealth += health;
	OnHPDamageDelegate.Broadcast(GetHealthRatio());

	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}

}

void UStatComponent::RegenerateStamina(float stamina)
{
	CurrentStamina += stamina;
	OnStaminaDamageDelegate.Broadcast();

	if (CurrentStamina >= MaxStamina)
	{
		CurrentStamina = MaxStamina;
	}
}

bool UStatComponent::CheckHPZero()
{
	return CurrentHealth <= 0.0f ? true : false;
}

bool UStatComponent::CheckStaminaZero()
{
	return CurrentStamina <= 0.0f ? true : false;
}

