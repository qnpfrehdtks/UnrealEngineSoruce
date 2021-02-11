// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Actor\AICharacterBase.h"
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
#include "Components/WidgetComponent.h"

#include "Widget/InventoryUserWidget.h"

#include "Utils/LowpolyPlayerContorller.h"
#include "Utils/LowPolyGameInstance.h"

#include "State/IdleState.h"
#include "State/CombatState.h"


#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

#include "Actor/ItemBase.h"
#include "Components/WidgetComponent.h"
#include "TimerManager.h"
#include "Materials/MaterialInstance.h"

#include "Particles/ParticleSystemComponent.h"

AAICharacterBase::AAICharacterBase()
{
	currentPhase = ECharacterPhase::ECP_PHASE_01;
	teamID = FGenericTeamId(10);

}

void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	/* 특정 체력이 되면 Phase 변화시킴.*/
	//StatComponent->OnHPDamageDelegate.AddUObject(this, &AAICharacterBase::ChangePhase);

	TargetingComponent->OnTargetingDelegate.AddLambda
	(
		[this]()
		{
			GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		}
	);



}

void AAICharacterBase::Dead()
{
	Super::Dead();

	if (CharacterType != ECharacterType::ECT_Boss) return;

	ALowpolyPlayerContorller* controller = Cast<ALowpolyPlayerContorller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (controller != nullptr)
	{
		controller->VisibleVictoryMessage(true);
	}
}

void AAICharacterBase::Attack()
{
	if (FSM == nullptr) return;
	if (!FSM->bCanInput) return;

	ECharacterState state = FSM->GetState();

	if (state != ECharacterState::ECS_Idle && state != ECharacterState::ECS_Walk) return;
	
	//FSM->HandleInput(EInputEvent::IE_Pressed, EKeys::LeftMouseButton);
	UE_LOG(LogTemp, Warning, TEXT("Attack!!"));

	int attackIDX = FMath::RandRange(0, 4);

	switch (attackIDX)
	{
	case 0:
		FSM->PushState(ECharacterState::ECS_Attack1);
		break;
	case 1:
		FSM->PushState(ECharacterState::ECS_Attack2);
		break;
	case 2:
		FSM->PushState(ECharacterState::ECS_Attack3);
		break;
	case 3:
		FSM->PushState(ECharacterState::ECS_Attack4);
		break;
	case 4:
		FSM->PushState(ECharacterState::ECS_Attack5);
		break;
	default:
		break;
	}

}

void AAICharacterBase::PlayForceState(ECharacterState state)
{
	if (FSM == nullptr) return;

	ECharacterState currentState = FSM->GetState();

	if (currentState != ECharacterState::ECS_Idle && currentState != ECharacterState::ECS_Walk) return;

	FSM->PopAllState();
	FSM->PushState(state);
}

/* AI는 AI Behavior에서 실행. */
void AAICharacterBase::SelectState(ECharacterState state)
{
	if (FSM == nullptr) return;
	if (!FSM->bCanInput) return;

	ECharacterState currentState = FSM->GetState();

	if (currentState != ECharacterState::ECS_Idle && currentState != ECharacterState::ECS_Walk) return;

	FSM->PushState(state);
}

void AAICharacterBase::ChangePhase(float healthRatio)
{
	if (currentPhase == ECharacterPhase::ECP_PHASE_01 && CharacterType == ECharacterType::ECT_Boss)
	{
		if (healthRatio <= 0.4f)
		{
			FSM->PopAllState();
			FSM->PushState(ECharacterState::ECS_Drink);

			currentPhase = ECharacterPhase::ECP_PHASE_02;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("IsRim"), 1.0f);
			FSM->animationSpeed = 1.25f;

			auto particleSystem = UGameplayStatics::SpawnEmitterAttached(
				rageParticle,
				GetMesh(), TEXT("spine_01"), FVector::UpVector * 0.0f, FRotator(-90, 0, 0), EAttachLocation::KeepRelativeOffset, true);

			particleSystem->SetWorldScale3D(FVector(0.6f, 0.6f, 0.6f));

		}
	}
}

void AAICharacterBase::OnStartTargeting_Implementation(AActor* actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Target On"));

	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	if (TargetingWidget)
		TargetingWidget->SetVisibility(true);

	if (HPBarWidget)
		HPBarWidget->SetVisibility(true);

	TargetingComponent->AddTargetingMEObject(actor);

}

