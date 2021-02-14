// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Targetable.h"
#include "Interface/Attackable.h"

#include "Enums/CharacterEnums.h"
#include "Enums/ItemEnums.h"
#include "GenericTeamAgentInterface.h"

#include "LowpolyCharacter.generated.h"
//#include <Runtime\AIModule\Classes\EnvironmentQuery\EnvQueryDebugHelpers.h>
//#include <Runtime\AIModule\Classes\EnvironmentQuery\EnvQueryDebugHelpers.h>

UCLASS()
class LOWPOLYDUNGEON_API ALowpolyCharacter : public ACharacter, public ITargetable, public IAttackable, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALowpolyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	FRotator currentRotator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	class UFSMComponent* FSM;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	class UTargetingComponent* TargetingComponent;


	// 캐릭터의 스,
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	class UStatComponent* StatComponent;

	// 장비의 정보를 담은 컴포넌트입니다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	class UEquipmentComponent* EquipComponent;

	// 플레이어와 오브젝트가 상호작용할 시 처리하는 루틴을 담은 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	class UInteractComponent* InteractComponent;

	// 인벤토리 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryComponent;

	//피격시 재생되는 히트 이펙트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle")
	class UParticleSystem* HitEffect;

	// 피격시 발생하는 사운드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* HitSoundCue;

	// 캐릭터의 HPBar 위젯
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* HPBarWidget;

	// 타겟팅 할 시 띄울 위젯
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* TargetingWidget;

	// 사망시 띄우는 메세지 위젯
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* DyingMessageWidget;

	// 승리시 띄우는 메세지 위젯
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* VictoryMessageWidget;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Colliison", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* interactHitCollsion;

	UPROPERTY()
	class ALowpolyPlayerContorller* playerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	ECharacterType CharacterType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsinvincibility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDestroying;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float DissolveAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float DistX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
	float DeadTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float DistY;

	UFUNCTION(BlueprintCallable)
	float GetStamina();

	UFUNCTION(BlueprintCallable)
	void consumeStamina(float stamina);

	UFUNCTION(BlueprintCallable)
	void consumeHealth(float hp);

	UFUNCTION(BlueprintCallable)
	void UseEquippedItem(EItemEquipmentType equipType, int32 index);

	UFUNCTION(BlueprintCallable)
	void UseSelectedItem(int32 index);

	UFUNCTION(BlueprintCallable)
	void OnSelectTarget();

	UFUNCTION(BlueprintCallable)
	virtual void Dead();

	UFUNCTION()
	void PostDeadTimer();

	UFUNCTION(BlueprintCallable)
	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	void Dodge();

	UFUNCTION(BlueprintCallable)
	void OnBlock();

	UFUNCTION(BlueprintCallable)
	void RepeatBlock();

	UFUNCTION(BlueprintCallable)
	void OffBlock();

	// E키 입력시 아이템 사용
	UFUNCTION()
	void UseItem();

	// 아이템과 상호작용시 실행 함수
	UFUNCTION()
	void InteractObject();

	//장착된 아이템 변경시 실행.
	UFUNCTION()
	void ChangeEquippedItem();

	// 앞으로 이동시 실행 함수.
	UFUNCTION()
	void MoveForward(float value);
	UFUNCTION()
	void MoveRight(float value);
	UFUNCTION()
	void Turn(float value);
	UFUNCTION()
	void LookAt(float value);

	UFUNCTION()
	void TargetOn();

	UFUNCTION()
	void OnSprint();

	UFUNCTION()
	void RepeatSprint();

	UFUNCTION()
	void OffSprint();

	UFUNCTION()
	void activeInventory();

	UFUNCTION(BlueprintCallable)
	ECharacterState GetState();

	/* Inventory */
	UFUNCTION()
	void InsertToInventory(class AItemBase* item);

	UFUNCTION()
	ESlateVisibility GetInventoryVisiblity();

	/* Equipment 관련 */
	void EquipItemFromInventory(const int32 itemID);

	/* Equipment 관련 */
	void UnEquipItemFromInventory(const int32 itemID);

	/* Dead 타임 시간 이후 발생하는 함수. */
	FTimerHandle DeadTimer;

	/* 충돌시 발생 함수.. */
	UFUNCTION()
	void OnHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// ============== 인터페이스 ====================
	virtual void OnStartTargeting_Implementation(AActor* actor) override;
	virtual void OnEndTargeting_Implementation(AActor* actor) override;

	virtual bool OnDamaged_Implementation(AActor* Attacker, float Damage, FVector attackPostion, FVector attackDir, EAttackType attackType) override;


	protected:
	/** Retrieve team identifier in form of FGenericTeamId */
	FGenericTeamId GetGenericTeamId() const;

	FGenericTeamId teamID;
//	FGenericTeamId GetGenericTeamId() const { return teamID; }

};
