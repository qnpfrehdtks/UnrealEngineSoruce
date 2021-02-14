// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/CharacterEnums.h"
#include "FSMComponent.generated.h"

/* 이 조건에 갈 수있는가? 체크하는 bool 리턴하는 델리게이트. 스테이트마다 다르다 */
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckEnterStateDelegate_float, float);
/* 이 조건에 갈 수있는가? 체크하는 bool 리턴하는 델리게이트. 스테이트마다 다르다 */
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckEnterStateDelegate, class UStateBase*);
DECLARE_DELEGATE_RetVal_OneParam(bool, FCheckUpdateStateDelegate, class UStateBase*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFSMComponent();

	/* 소유한 캐릭터 주인*/
	UPROPERTY( VisibleAnywhere ,BlueprintReadWrite, Category = "Character")
	class ALowpolyCharacter* ownedCharacter;

	/* 현재 캐릭터 상태 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UStateBase* currentState;

	/* 캐릭터가 담고 있는 State들의 map*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	TMap<ECharacterState, UStateBase*> StateMap;

	/* 미사용 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<UStateBase>> StateArray;

	/* 디퐅트 스테이트입니다. Stack에 모든 State가 pop되면 실행되는 State*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	ECharacterState StartState;

	/* 디퐅트 스테이트입니다. Stack에 모든 State가 pop되면 실행되는 State*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	ECharacterState ResverdState;

	/* 입력이 가능한가? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	bool bCanInput;

	/* 애니메이션 스피드 */
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

	/* 내가 가진 State 검색.*/
	UFUNCTION(BlueprintCallable)
	UStateBase* FindState(ECharacterState eState);

	/* 입력 Key값에 따라 State가 달라질 수 있으므로 실행하는 함수. */
	UFUNCTION()
	void HandleInput(EInputEvent Input, FKey key, float axisValue = 0.0f);

	/* State 변경*/
	UFUNCTION(BlueprintCallable)
	bool ChangeState(ECharacterState eState);

	UFUNCTION(BlueprintCallable)
	bool PlayReserveState();


	UFUNCTION(BlueprintCallable)
	void ReserveState(ECharacterState eState);

	/* 스태미나가 드는 경우, 이 함수를 실행시켜라.*/
	UFUNCTION(BlueprintCallable)
	bool ChangeState_float(ECharacterState eState, float _consumeStamina);

	/* 현재 스테이트 enum 가져오기 */
	UFUNCTION(BlueprintPure)
	ECharacterState GetState();

	/* 데미지 들어올 시 처리 : 블루프린트 상에서 처리. */
	UFUNCTION(BlueprintCallable)
	float GetDamaged(EAttackType attackType, FVector attackPosition, float DMG);

};
