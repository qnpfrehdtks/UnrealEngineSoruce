// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/CharacterEnums.h"
#include "Engine/DataTable.h"
#include "StateBase.generated.h"

/* 스테이트 업데이트 델리게이트 */
DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateStateDelegate, float);
/* 스테이트 입장시 델리게이트 */
DECLARE_MULTICAST_DELEGATE(FEnterStateDelegate);
/* 스테이트 종료시 델리게이트 */
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

	/* 무빙이 가능한가? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	bool bCanMove;

	/* 소비 스테미나 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float consumeStamina;

	/* 스테미나 회복 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float plusStaminaPerSec;

	/* 타겟 카메라가 가능한 상태인지? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetCamera;

	/* 타겟에 대한 회전이 가능한지? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	bool bIsTargetRotation;

	/* 어떤 에님 몽타주를 쓰는지 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* anim;

	/* Value 값들인데, 주로 공격력 Value를 집어넣어서 사용 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TMap<FString, float> Attribute;

	/* */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName sectionName;

	/* 애니메이션 재생 속도*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float playRate;

	/* 공격력의 얼마만큼만 받을 것인지?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float blockRate;

	/*  스테이트 블프 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TSubclassOf<UStateBase> StateClass;

	/* 공격 타입은 ? 강공격, 약공격 등등*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	EAttackType attackType;

	/* 만약 피격 당할 시 어떤 액션을 취할것인가? 슈퍼아머 - 절대 피격 애니메이션을 재생하지 않는다 등*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Only Attack")
	ECharacterHitArmor attackArmor;

};

/**
 * 
 */
/* 블루 프린트로 빼서 사용가능. */
UCLASS()
class LOWPOLYDUNGEON_API UStateBase : public UObject
{
	GENERATED_BODY()
public:
	UStateBase();

	// 블루 프린트에서 사용가능한 이벤트 함수.
	UFUNCTION(BlueprintNativeEvent)
	 void Init(const FStateData& newData);
	 virtual void Init_Implementation(const FStateData& newData);

	 /* 키값 처리. */
	 UFUNCTION(BlueprintNativeEvent)
	 void HandleInput(EInputEvent Input, FKey key, float axisValue);
	 virtual void HandleInput_Implementation(EInputEvent Input, FKey key, float axisValue);

	 /* 스테이트 입장시 처리 함수 */
	 UFUNCTION(BlueprintNativeEvent)
	 void Enter(float animationplayRate);
	 virtual void Enter_Implementation(float animationplayRate);

	 /* 스테이트 업데이트 시 처리 함수*/
	 UFUNCTION(BlueprintNativeEvent)
	 void Update(float DeltaTime);
	 virtual void Update_Implementation(float DeltaTime);

	 /* 데미지 입을 시 처리 함수 */
	 virtual float Damaged(EAttackType dmgType, FVector dmgPosition, float DMG);

	 /* 스테이트 종료시 처리 함수 */
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
