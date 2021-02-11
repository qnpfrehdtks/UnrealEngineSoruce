// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/Attackable.h"

// Add default functionality here for any IAttackable functions that are not pure virtual.

IAttackable::IAttackable()
{

}


bool IAttackable::OnDamaged_Implementation(AActor* Attacker, float Damage, FVector attackPostion, FVector attackDir,EAttackType attackType)
{
	return true;
}
