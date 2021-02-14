// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/LowpolyCharacter.h"
#include "Actor/ItemBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h" 

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Sound/SoundCue.h"

// Custom include 

#include "Component/StatComponent.h"
#include "Component/FSMComponent.h"
#include "Component/TargetingComponent.h"
#include "Component/EquipmentComponent.h"
#include "Component/InteractComponent.h"
#include "Component/InventoryComponent.h"

#include "Widget/InventoryUserWidget.h"

#include "Utils/LowpolyPlayerContorller.h"
#include "Utils/LowPolyGameInstance.h"
#include "Utils/LowPolyDungeonGameModeBase.h"

#include "State/IdleState.h"
#include "State/CombatState.h"


#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

#include "Actor/ItemBase.h"
#include "Components/WidgetComponent.h"
#include "TimerManager.h"


// Sets default values
ALowpolyCharacter::ALowpolyCharacter()
{
 	 // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	 PrimaryActorTick.bCanEverTick = true;

	 interactHitCollsion = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	 interactHitCollsion->SetSphereRadius(200.0f);
	 interactHitCollsion->SetupAttachment(GetRootComponent());

	 SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	 SpringArm->SetupAttachment(GetRootComponent());

	 Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	 Camera->SetupAttachment(SpringArm);

	 FSM = CreateDefaultSubobject<UFSMComponent>(TEXT("FSM"));
	 StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));

	 TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));

	 EquipComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipComponent"));

	 InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));

	 InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	 HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	 HPBarWidget->SetupAttachment(GetRootComponent());

	 TargetingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetingWidget"));
	 TargetingWidget->SetupAttachment(GetRootComponent());

	 DyingMessageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DyingWidget"));
	 DyingMessageWidget->SetupAttachment(GetRootComponent());

	 SpringArm->bEnableCameraRotationLag = true;
	 SpringArm->bEnableCameraLag = true;
	 SpringArm->bUsePawnControlRotation = true;

	 SpringArm->CameraLagSpeed = 5.5f;
	 SpringArm->CameraRotationLagSpeed = 5.5f;

	 SpringArm->TargetArmLength = 450.0f;
	 Camera->bUsePawnControlRotation = false;
	 bUseControllerRotationYaw = false;
	 bUseControllerRotationPitch = false;
	 bUseControllerRotationRoll = false;

	 bIsinvincibility = false;

	 DissolveAmount = 0.0f;

	 interactHitCollsion->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	 interactHitCollsion->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	 interactHitCollsion->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	 DeadTime = 3.0f;

	 teamID = FGenericTeamId(5);

}

// Called when the game starts or when spawned
void ALowpolyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipComponent->EquipDefaultItem(GetMesh());

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	
	playerController = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	TargetingComponent->OnTargetingDelegate.AddUObject(this, &ALowpolyCharacter::OnSelectTarget);

	FSM->CheckEnterDelegate.BindLambda(
		[this](UStateBase* state)->bool
		{
			if (state->consumeStamina <= StatComponent->CurrentStamina)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	);

	FSM->CheckEnterDelegate_float.BindLambda(
		[this](float dmg)->bool
		{
			if (dmg <= StatComponent->CurrentStamina)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	);

	StatComponent->OnStaminaZeroDelegate.AddLambda(
		[this]()
		{
			if (FSM->currentState->EState == ECharacterState::ECS_Sprint)
				FSM->ChangeState(ECharacterState::ECS_Walk);
			//if (FSM->currentState->EState == ECharacterState::ECS_Block)
			//	FSM->PopState();
		}
	);

	StatComponent->OnHPZeroDelegate.AddLambda(
		[this]()
		{
			Dead();
		}
	);

	if(HPBarWidget)
		HPBarWidget->SetVisibility(false);

	if (TargetingWidget)
		TargetingWidget->SetVisibility(false);

	DistX = HPBarWidget->GetDrawSize().X;
	DistY = HPBarWidget->GetDrawSize().Y;

	interactHitCollsion->OnComponentBeginOverlap.AddDynamic(this, &ALowpolyCharacter::OnHitCollisionToItem);
	interactHitCollsion->OnComponentEndOverlap.AddDynamic(this, &ALowpolyCharacter::EndHitCollisionToItem);
	FSM->Start();
}

// Called every frame
void ALowpolyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 캐릭터의 스태미너와 체력 리젠과 관련된 코드
	if (FSM != nullptr)
	{
		if (FSM->currentState != nullptr && FSM->currentState->plusStaminaPerSecond > 0.01f)
		{
			StatComponent->RegenerateStamina(FSM->currentState->plusStaminaPerSecond * DeltaTime);
		}
		else if(FSM->currentState != nullptr && FSM->currentState->plusStaminaPerSecond < -0.01f)
		{
			StatComponent->DamageStamina(-FSM->currentState->plusStaminaPerSecond * DeltaTime);
		}
	}

	// 만약 캐릭터가 사망시 처리하게 되는 루틴
	if (bIsDestroying)
	{
		auto arr = GetMesh()->GetAttachChildren();

		for (auto m : arr)
		{
			USkeletalMeshComponent* ChildSkeleton = Cast<USkeletalMeshComponent>(m);

			if (ChildSkeleton)
			{
				// 메테리얼을 가져와서 디졸브 쉐이더 실행.
				ChildSkeleton->SetScalarParameterValueOnMaterials(TEXT("DissolveAmount"), DissolveAmount );
			}
		}

		DissolveAmount += DeltaTime * 0.1f;
	}

	// 타겟팅 카메라와 관련된 코드
	if (FSM->currentState != nullptr)
	{
		if (FSM->currentState->bIsTargetCamera)
		{
			TargetingComponent->OnTargetUpdateCamera(DeltaTime);
		}
		if (FSM->currentState->bIsTargetRotation)
		{
			TargetingComponent->OnTargetUpdateRotation(DeltaTime);
		}
	}
}

// Called to bind functionality to input
void ALowpolyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//  키 입력과 관련된 코드입니다.

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ALowpolyCharacter::Attack);

	PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &ALowpolyCharacter::Dodge);
	PlayerInputComponent->BindAction(TEXT("TargetOn"), IE_Pressed, this, &ALowpolyCharacter::TargetOn);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ALowpolyCharacter::OnSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Repeat, this, &ALowpolyCharacter::RepeatSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ALowpolyCharacter::OffSprint);

	PlayerInputComponent->BindAction(TEXT("ItemUse"), IE_Pressed, this, &ALowpolyCharacter::UseItem);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ALowpolyCharacter::InteractObject);

	PlayerInputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ALowpolyCharacter::activeInventory);

	PlayerInputComponent->BindAction(TEXT("EquippedItemChange"), IE_Pressed, this, &ALowpolyCharacter::ChangeEquippedItem);

	PlayerInputComponent->BindAction(TEXT("Block"), IE_Pressed, this, &ALowpolyCharacter::OnBlock);
	PlayerInputComponent->BindAction(TEXT("Block"), IE_Repeat, this, &ALowpolyCharacter::RepeatBlock);
	PlayerInputComponent->BindAction(TEXT("Block"), IE_Released, this, &ALowpolyCharacter::OffBlock);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ALowpolyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ALowpolyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ALowpolyCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookAt"), this, &ALowpolyCharacter::LookAt);
}

void ALowpolyCharacter::UseItem()
{
	// E키 입력시 아이템 사용
	FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::E);
}

void ALowpolyCharacter::InteractObject()
{
	// 아이템과 인터렉션 하기 위한 함수
	InteractComponent->InteractToObject();
}

void ALowpolyCharacter::ChangeEquippedItem()
{
	// 현재 들고 있는 아이템 스위치하기 위한 함수.
	if (EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand) ||
		EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_Back))
		FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::R);
}

void ALowpolyCharacter::UseSelectedItem(int32 index)
{
	// 선택된 아이템 사용 (보통 인벤토리내에 슬롯을 사용시)
	EquipComponent->UseSelectedItem(index);
}

float ALowpolyCharacter::GetStamina()
{
	//스태미너를 가져옵니다.
	return StatComponent->CurrentStamina;
}

void ALowpolyCharacter::consumeStamina(float stamina)
{
	// 스태미너를 소비합니다.
	StatComponent->DamageStamina(stamina);
}

void ALowpolyCharacter::consumeHealth(float hp)
{
	// HP를 소비합니다.
	StatComponent->DamageHealth(hp);
}

void ALowpolyCharacter::UseEquippedItem(EItemEquipmentType equipType, int32 index)
{
	// 장착된 아이템을 사용합니다.
	EquipComponent->UseItem(equipType, index);
}


// 타겟할 대상을 선택할 시 실행되는 함수입니다.
void ALowpolyCharacter::OnSelectTarget()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

}

//죽음 발생시 실행되는 함수입니다.
void ALowpolyCharacter::Dead()
{
	/* Dead timer 발생. */
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorld()->GetTimerManager().SetTimer(DeadTimer,this, &ALowpolyCharacter::PostDeadTimer, DeadTime, false);

	// 타겟팅 상대를 제거.
	TargetingComponent->UnLockTarget();
	TargetingComponent->UnLockTargetByMyself();

	// 스테이트는 죽음으로
	FSM->ChangeState(ECharacterState::ECS_Dead);

	// 보스가 아니하면 시체를 래그돌로 처리합니다.
	if (CharacterType != ECharacterType::ECT_Boss)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	}

	//나는 이제 삭제중.
	bIsDestroying = true;

	if(InventoryComponent)
		playerController->SetVisibleInventory_Implementation(false);

	if (CharacterType != ECharacterType::ECT_Player) return;

	ALowpolyPlayerContorller* controller = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (controller != nullptr)
	{
		// 죽었다하는 widget 메세지 띄워줍니다.
		controller->VisibleDyingMessage(true);
	}

	ALowPolyDungeonGameModeBase* gameMode = Cast<ALowPolyDungeonGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (gameMode != nullptr)
	{
		// 현재 전투 UI를 안보이게 처리합니다.
		gameMode->SetBattleModeUIVisible(false);
	}

}

// 죽은 후, 3초뒤에 처리할 타이머의 콜백함수입니다.
void ALowpolyCharacter::PostDeadTimer()
{
	AItemBase* weapon = EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand);
	if (weapon)
	{
		weapon->Destroy();
	}

	if (HPBarWidget)
	{
		HPBarWidget->SetVisibility(false);
	}

	if (TargetingWidget)
		TargetingWidget->SetVisibility(false);

//	FSM->AllClearState();

	Destroy();
}

void ALowpolyCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack!!"));
	
	if (EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand))
		FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::LeftMouseButton);
	else if (EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_Back))
		ChangeEquippedItem();
}

// 회피시 실행되는 함수.
void ALowpolyCharacter::Dodge()
{
	FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::SpaceBar);
}


// 방어 처음 시작시 실행.
void ALowpolyCharacter::OnBlock()
{
	if (EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand))
		FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::RightMouseButton);
}

// 블록 반복시 실행.
void ALowpolyCharacter::RepeatBlock()
{
	if (EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand))
	FSM->HandleInput(EInputEvent::IE_Repeat, EKeys::RightMouseButton);
}

// 방어 풀 시 실행되는 함수.
void ALowpolyCharacter::OffBlock()
{
	if (EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand))
	FSM->HandleInput(EInputEvent::IE_Released, EKeys::RightMouseButton);
}

// 무브 포워드
void ALowpolyCharacter::MoveForward(float value)
{
	if (FSM->currentState != nullptr && FSM->currentState->bCanMove)
	{
		FRotator rot = FRotator(0, GetControlRotation().Yaw, 0);
		FVector forward = UKismetMathLibrary::GetForwardVector(rot);
		AddMovementInput(forward, value);
	}
}

void ALowpolyCharacter::MoveRight(float value)
{
	if (FSM->currentState != nullptr && FSM->currentState->bCanMove)
	{
		FRotator rot = FRotator(0, GetControlRotation().Yaw, 0);
		FVector right = UKismetMathLibrary::GetRightVector(rot);
		AddMovementInput(right, value);
	}
}

// 마우스를 상하이동시 
void ALowpolyCharacter::Turn(float value)
{
	if(TargetingComponent->TargetObject == nullptr)
		AddControllerYawInput(value);
}

// 마우스 좌우 이동시
void ALowpolyCharacter::LookAt(float value)
{
	AddControllerPitchInput(value);
}

// 상대를 타겟하는 키를 입력시
void ALowpolyCharacter::TargetOn()
{
	FVector pos;
	FRotator rot;
	GetController()->GetPlayerViewPoint(pos, rot);
	TargetingComponent->ChangeLockOnTarget(pos, rot);
}

// 달리기 모드를 해제할 시
void ALowpolyCharacter::OffSprint()
{
	FSM->HandleInput(EInputEvent::IE_Released, EKeys::Q);
}

// 인벤토리를 엽니다.
void ALowpolyCharacter::activeInventory()
{
	if (bIsDestroying == true) return;

	if (playerController != nullptr)
	{
		InventoryComponent->UpdateInventory();
		playerController->ToggleInventoryUI();
	}
}

//캐릭터의 상태 값을 가져옵니다.
ECharacterState ALowpolyCharacter::GetState()
{
	if (FSM == nullptr)
		return ECharacterState::ECS_None;

	return FSM->GetState();
}

void ALowpolyCharacter::InsertToInventory(AItemBase* item)
{
	ULowPolyGameInstance* gameInstance = Cast<ULowPolyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstance != nullptr)
	{
		InventoryComponent->InsertInventory(item);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No DataInstance"));
	}
}

ESlateVisibility ALowpolyCharacter::GetInventoryVisiblity()
{
	if (playerController == nullptr)
	{
		return ESlateVisibility::Hidden;
	}

	if (playerController->InventoryWidget == nullptr)
	{
		return ESlateVisibility::Hidden;
	}

	return playerController->InventoryWidget->GetVisibility();
}

void ALowpolyCharacter::EquipItemFromInventory(const int32 itemID)
{
	AItemBase* selectedItem = InventoryComponent->GetItemFromInventory(itemID);

	if (selectedItem != nullptr)
	{
		EquipComponent->Equip(GetMesh(), selectedItem, true);
		InventoryComponent->UpdateInventory();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Equip Fail"));
	}
}

void ALowpolyCharacter::UnEquipItemFromInventory(const int32 itemID)
{
	AItemBase* selectedItem = InventoryComponent->GetItemFromInventory(itemID);

	if (selectedItem != nullptr)
	{
		EItemType itemType = selectedItem->GetItemType();
		EItemEquipmentType eType = EquipComponent->ConvertToEquipType(itemType);
		EquipComponent->Unequip(GetMesh(), eType);
		InventoryComponent->UpdateInventory();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory UnEquip Fail"));
	}
}

void ALowpolyCharacter::OnSprint()
{
	FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::Q);
}

void ALowpolyCharacter::RepeatSprint()
{
	FSM->HandleInput(EInputEvent::IE_Repeat, EKeys::Q);
}

void ALowpolyCharacter::OnStartTargeting_Implementation(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Target On"));

	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	//if (TargetingWidget)
	//	TargetingWidget->SetVisibility(true);

	//if (HPBarWidget)
	//	HPBarWidget->SetVisibility(true);

	TargetingComponent->AddTargetingMEObject(actor);

}

void ALowpolyCharacter::OnEndTargeting_Implementation(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Target Off"));

	//if (HPBarWidget)
		//HPBarWidget->SetVisibility(false);

	if (TargetingWidget)
		TargetingWidget->SetVisibility(false);

	TargetingComponent->RemoveTargetingMeObject(actor);
}

bool ALowpolyCharacter::OnDamaged_Implementation(AActor* Attacker,float Damage, FVector attackPostion, FVector attackDir, EAttackType attackType)
{
	if (bIsinvincibility)
	{
		return false;
	}
	else
	{
		bIsinvincibility = true;
	}

	IGenericTeamAgentInterface* otherTeamID = Cast<IGenericTeamAgentInterface>(Attacker);
	if (otherTeamID == nullptr)
		return false;

	if (teamID == otherTeamID->GetGenericTeamId())
		return false;

	if (HitEffect)
	{
		FVector characterRotationDir = Attacker->GetActorLocation();
		characterRotationDir.Z = GetActorLocation().Z;

		currentRotator = UKismetMathLibrary::MakeRotFromX((characterRotationDir - GetActorLocation()).GetSafeNormal());

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), attackPostion);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, attackPostion, rot, true);
	}

	if (HitSoundCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HitSoundCue);
	}

	if (HPBarWidget)
	{
		HPBarWidget->SetVisibility(true);
	}

	Damage = FSM->GetDamaged(attackType, attackPostion, Damage);
	StatComponent->DamageHealth(Damage);
//	DrawDebugCapsule(GetWorld(), (topSocketPosition + bottomSocketPosition) * 0.5f, shape.Capsule.HalfHeight, 30.0f, rot.Quaternion(), FColor::Green, false, 2.0f);
	
	return true;
}

FGenericTeamId ALowpolyCharacter::GetGenericTeamId() const
{
	return teamID;
}

void ALowpolyCharacter::OnHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact : %s"), *(OtherActor->GetName()));


	TArray<AActor*> arryActor;
	interactHitCollsion->GetOverlappingActors(arryActor);

	for (int i = 0; i < arryActor.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact : %s"), *(arryActor[i]->GetName()));
	}

	UE_LOG(LogTemp, Warning, TEXT("Interact Count : %d"), arryActor.Num());

	InteractComponent->FindClosestInteractObject(arryActor);
}

void ALowpolyCharacter::EndHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> arryActor;
	interactHitCollsion->GetOverlappingActors(arryActor);

	UE_LOG(LogTemp, Warning, TEXT("End Interact Count : %d"), arryActor.Num());

	InteractComponent->FindClosestInteractObject(arryActor);
}



