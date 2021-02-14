// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/CharacterEnums.h"
#include "FSMComponent.generated.h"

/* �� ���ǿ� �� ���ִ°�? üũ�ϴ� bool �����ϴ� ��������Ʈ. ������Ʈ���� �ٸ��� */
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckEnterStateDelegate_float, float);
/* �� ���ǿ� �� ���ִ°�? üũ�ϴ� bool �����ϴ� ��������Ʈ. ������Ʈ���� �ٸ��� */
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckEnterStateDelegate, class UStateBase*);
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckUpdateStateDelegate, class UStateBase*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFSMComponent();

	/* ������ ĳ���� ����*/
	UPROPERTY( VisibleAnywhere ,BlueprintReadWrite, Category = "Character")
	class ALowpolyCharacter* ownedCharacter;

	/* ���� ĳ���� ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UStateBase* currentState;

	/* ĳ���Ͱ� ��� �ִ� State���� map*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	TMap<ECharacterState, UStateBase*> StateMap;

	/* �̻�� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<UStateBase>> StateArray;

	/* ��jƮ ������Ʈ�Դϴ�. Stack�� ��� State�� pop�Ǹ� ����Ǵ� State*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	ECharacterState StartState;

	/* ��jƮ ������Ʈ�Դϴ�. Stack�� ��� State�� pop�Ǹ� ����Ǵ� State*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	ECharacterState ResverdState;

	/* �Է��� �����Ѱ�? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	bool bCanInput;

	/* �ִϸ��̼� ���ǵ� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	float animationSpeed;

	FCheckEnterStateDelegate CheckEnterDelegate;
	FCheckUpdateStateDelegate CheckUpdateDelegate;

	FCheckEnterStateDelegate_float CheckEnterDelegate_float;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	class UDataTable* StateData;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Start();

	/* ���� ���� State �˻�.*/
	UFUNCTION(BlueprintCallable)
	UStateBase* FindState(ECharacterState eState);

	/* �Է� Key���� ���� State�� �޶��� �� �����Ƿ� �����ϴ� �Լ�. */
	UFUNCTION()
	void HandleInput(EInputEvent Input, FKey key, float axisValue = 0.0f);

	/* State ����*/
	UFUNCTION(BlueprintCallable)
	bool ChangeState(ECharacterState eState);

	UFUNCTION(BlueprintCallable)
	bool PlayReserveState();


	UFUNCTION(BlueprintCallable)
	void ReserveState(ECharacterState eState);

	/* ���¹̳��� ��� ���, �� �Լ��� ������Ѷ�.*/
	UFUNCTION(BlueprintCallable)
	bool ChangeState_float(ECharacterState eState, float _consumeStamina);

	/* ���� ������Ʈ enum �������� */
	UFUNCTION(BlueprintPure)
	ECharacterState GetState();

	/* ������ ���� �� ó�� : �������Ʈ �󿡼� ó��. */
	UFUNCTION(BlueprintCallable)
	float GetDamaged(EAttackType attackType, FVector attackPosition, float DMG);

};
