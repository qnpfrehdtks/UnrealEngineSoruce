// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/CharacterEnums.h"
#include "Attackable.generated.h"


/* 언리얼 인터페이스 */
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

/* 공격 데미지를 입을 수 있는 오브젝트는 이 인터페이스를 구현해서 사용하세요. */
class LOWPOLYDUNGEON_API IAttackable
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IAttackable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Targeting")
	bool OnDamaged(AActor* Attacker, float Damage,FVector attackPostion, FVector attackDir, EAttackType attackType);
	virtual bool OnDamaged_Implementation(AActor* Attacker, float Damage, FVector attackPostion, FVector attackDir, EAttackType attackType);




};
