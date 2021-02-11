// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/CharacterEnums.h"
#include "Engine/DataTable.h"
#include "StateBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateStateDelegate, float);
DECLARE_MULTICAST_DELEGATE(FEnterStateDelegate);
DECLARE_MULTICAST_DELEGATE(FEndStateDelegate);

USTRUCT(BlueprintType)
struct FStateData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStateData()
	{
		blockRate = 1.0f;
		playRate = 1.0f;
		sectionName = NAME_None;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState CharacterState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float consumeStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float plusStaminaPerSec;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TMap<FString, float> Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName sectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float playRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float blockRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TSubclassOf<UStateBase> StateClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	EAttackType attackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	ECharacterHitArmor attackArmor;

};

/**
 * 
 */
UCLASS()
class LOWPOLYDUNGEON_API UStateBase : public UObject
{
	GENERATED_BODY()
public:
	UStateBase();

	UFUNCTION(BlueprintNativeEvent)
	 void Init(const FStateData& newData);
	 virtual void Init_Implementation(const FStateData& newData);

	 UFUNCTION(BlueprintNativeEvent)
	 void HandleInput(EInputEvent Input, FKey key, float axisValue);
	 virtual void HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue);

	 UFUNCTION(BlueprintNativeEvent)
	 void Enter(float animationplayRate);
	 virtual void Enter_Implementation(float animationplayRate);

	 UFUNCTION(BlueprintNativeEvent)
	 void Update(float DeltaTime);
	 virtual void Update_Implementation(float DeltaTime);

	 virtual float Damaged(EAttackType dmgType, FVector dmgPosition, float DMG);

	 UFUNCTION(BlueprintNativeEvent)
	 void Exit();
	 virtual void Exit_Implementation();

protected:

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	ECharacterState EState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bCanOpenInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	class ALowpolyCharacter* OwnedPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	class UFSMComponent* FSMRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float elapsedTime;

	/* Data Driven */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	bool bCanMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float consumeStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float plusStaminaPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	class UAnimMontage* animMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FName sectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float playRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	float blockRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	EAttackType attackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	ECharacterHitArmor attackArmor;

	/* Delegate */
	FUpdateStateDelegate UpdateDelegate;
	FEnterStateDelegate EnterDelegate;
	FEndStateDelegate EndDelegate;
};
