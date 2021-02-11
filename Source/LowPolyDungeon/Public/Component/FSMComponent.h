// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/CharacterEnums.h"
#include "FSMComponent.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckEnterStateDelegate_float, float);

DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckEnterStateDelegate, class UStateBase*);
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckUpdateStateDelegate, class UStateBase*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFSMComponent();

	UPROPERTY( VisibleAnywhere ,BlueprintReadWrite, Category = "Character")
	class ALowpolyCharacter* ownedCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UStateBase* currentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UStateBase* topState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	TMap<ECharacterState, UStateBase*> StateMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<UStateBase>> StateArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TArray<UStateBase*> StateStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	ECharacterState StartState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	bool bCanInput;

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

	UFUNCTION(BlueprintCallable)
	UStateBase* FindState(ECharacterState eState);

	UFUNCTION()
	void HandleInput(EInputEvent Input, FKey key, float axisValue = 0.0f);

	UFUNCTION(BlueprintCallable)
	bool ReleaseAndPushState(ECharacterState eState);

	UFUNCTION(BlueprintCallable)
	bool ChangeState(ECharacterState eState);

	UFUNCTION(BlueprintCallable)
	bool PushState(ECharacterState eState);

	UFUNCTION(BlueprintCallable)
	bool PushState_float(ECharacterState eState, float _consumeStamina);

	UFUNCTION(BlueprintCallable)
	void PlayTopState();

	UFUNCTION(BlueprintCallable)
	void ReservePushState(ECharacterState eState);

	UFUNCTION(BlueprintCallable)
	void ReservePopState();

	UFUNCTION(BlueprintCallable)
	void PopState();

	UFUNCTION(BlueprintCallable)
	void PopAllState();

	UFUNCTION(BlueprintPure)
	ECharacterState GetState();

	UFUNCTION(BlueprintCallable)
	float GetDamaged(EAttackType attackType, FVector attackPosition, float DMG);

};
