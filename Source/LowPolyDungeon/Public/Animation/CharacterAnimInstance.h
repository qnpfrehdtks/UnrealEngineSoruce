// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UCharacterAnimInstance();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	class ALowpolyCharacter* myCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	bool bIsEquippedItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float moveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float moveDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	bool bIsFalling;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		

	
};
