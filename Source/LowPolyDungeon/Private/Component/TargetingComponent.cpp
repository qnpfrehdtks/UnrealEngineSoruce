// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TargetingComponent.h"
#include "Actor/LowpolyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;




	// ...
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	arrayTargetObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ActorsToIgnore.Add(GetOwner());

}

void UTargetingComponent::FindLockOnTarget(FVector start, FRotator dir)
{
	/* 처음 타겟팅 진행시 실행되는 함수. */
	ALowpolyCharacter* character = Cast<ALowpolyCharacter>(GetOwner());

	if (character == nullptr) return;
	
	FVector camDir = dir.Vector();
	FVector endPos = start + camDir * 3000.0f;

	TArray<AActor*> OverlappingActors;

	bool isHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(),
		TargetingRange, arrayTargetObjectType, nullptr, ActorsToIgnore, OverlappingActors);

	if (isHit)
	{
		for (auto& hitResult : OverlappingActors)
		{
			if (hitResult == nullptr) continue;
			if (hitResult == character)continue;

			FVector2D screenPos;

			if (UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), hitResult->GetActorLocation(), screenPos))
			{
				UnLockTarget();
				LockTarget(hitResult);
				break;
			}
		}
	}
	else
	{
		UnLockTarget();
	}
}

void UTargetingComponent::ChangeLockOnTarget(FVector start, FRotator dir)
{
	AActor* character = GetOwner();

	if (character == nullptr) return;

	FVector camDir = dir.Vector();
	FVector endPos = start + camDir * 3000.0f;

	TArray<AActor*> OverlappingActors;

	/* SphereOverlapActors 액터로 주변에 있는 액터를 검사한다. */
	bool isHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(),
		TargetingRange, arrayTargetObjectType, nullptr, ActorsToIgnore, OverlappingActors);

	float MaxDot = -1.0f;
	float MaxDistnce = 99999.0f;

	AActor* resultTarget = nullptr;

	/* 주변에 액터가 존재한다. */
	if (isHit)
	{
		/* 나의 카메라 가져온다. */
		APlayerCameraManager* camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FVector start = camera->GetCameraLocation();
		FVector forward = camera->GetActorForwardVector() * TargetingRange;
		
		for (auto& hitResult : OverlappingActors)
		{
			if (hitResult == nullptr) continue;
			if (hitResult == character)continue;
			
			FVector2D screenPos;

			/* 만약 스크린에 적 액터가 모습을 비치는지 체크 */
			if (UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), hitResult->GetActorLocation(), screenPos))
			{
				FVector toTargetDir = (hitResult->GetActorLocation() - start).GetSafeNormal();

				float dot = FVector::DotProduct(forward, toTargetDir);

				/* 카메라 방향벡터와 적에 대한 방향 벡터 내적을 통해 가장 큰 값을 타겟팅으로 삼는다. */
				if (MaxDot < dot)
				{
					MaxDot = dot;
					resultTarget = hitResult;
				}
			}
		}

		/* 언락하고 다시 타켓팅 */
		if (resultTarget != nullptr)
		{
			UnLockTarget();
			LockTarget(resultTarget);
		}
		else
		{
			UnLockTarget();
		}
	}
	else
	{
		UnLockTarget();
	}
}

void UTargetingComponent::UnLockTarget()
{
	if (TargetObject != nullptr)
	{
		ITargetable* oldTarget = Cast<ITargetable>(TargetObject);

		if (oldTarget != nullptr)
		{
			oldTarget->Execute_OnEndTargeting(TargetObject, GetOwner());
		}
	}

	TargetObject = nullptr;
}

bool UTargetingComponent::LockTarget(AActor* target)
{
	/* 타겟팅 되는 액터는 ITargetable를 상속받은 구현 클래스이여야 한다.*/
	ITargetable* newTarget = Cast<ITargetable>(target);
	if (newTarget != nullptr)
	{
		OnTargetingDelegate.Broadcast();

		TargetObject = target;

		/* LockOn 진행시 실행되는 인터페이스 함수.*/
		newTarget->Execute_OnStartTargeting(TargetObject, GetOwner());

		return true;
	}

	return false;
}

void UTargetingComponent::AddTargetingMEObject(AActor* target)
{
	arrTargeting.Add(target);
	return;
}

void UTargetingComponent::RemoveTargetingMeObject(AActor* target)
{
	if (target == nullptr || arrTargeting.Num() <= 0) return;

	arrTargeting.Remove(target);
	return;
}

void UTargetingComponent::UnLockTargetByMyself()
{
	/* 만약 타겟팅 되었다면 타겟팅을 스스로 풉니다. */
	if (arrTargeting.Num() == 0) return;

	for (int i = 0 ; i < arrTargeting.Num(); i++)
	{
		if (arrTargeting[i] == nullptr) continue;

		ALowpolyCharacter* character = Cast<ALowpolyCharacter>(arrTargeting[i]);

		if (character)
		{
			character->TargetingComponent->UnLockTarget();
		}
	}
}

void UTargetingComponent::OnTargetUpdateRotation(float DeltaTime)
{
	/* 타겟팅을 진행하면 실행되는 로테이션 함수. */
	if (TargetObject == nullptr) return;

	ALowpolyCharacter* character = Cast<ALowpolyCharacter>(TargetObject);

	if (character == nullptr) return;
	if (character->bIsDestroying) return;

	FVector startPos = GetOwner()->GetActorLocation();

	FVector targetPos = TargetObject->GetActorLocation();
	targetPos.Z = startPos.Z;

	/* 보간을 통해 진행. */
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(startPos, targetPos);
	FRotator targetRot = UKismetMathLibrary::RInterpTo(GetOwner()->GetActorRotation(), rot, DeltaTime, 28.0f);

	GetOwner()->SetActorRotation(targetRot.Quaternion());
}


void UTargetingComponent::OnTargetUpdateCamera(float DeltaTime)
{
	/* 카메라 또한 타겟팅을 향하도록 로테이션을 돌려주어야 한다. */
	if (TargetObject == nullptr) return;

	FVector targetPos = TargetObject->GetActorLocation(); //- TargetObject->GetActorRightVector() * 300.0f;

	ALowpolyCharacter* character = Cast<ALowpolyCharacter>(GetOwner());

	FVector cameraPos = character->Camera->GetComponentLocation();

	FRotator toTargetRot = UKismetMathLibrary::FindLookAtRotation(cameraPos, targetPos);
	FRotator resultRot = UKismetMathLibrary::RInterpTo(character->GetControlRotation(), toTargetRot, DeltaTime, 7.0f);

	resultRot = FRotator(character->GetControlRotation().Pitch, resultRot.Yaw, character->GetControlRotation().Roll);

	character->GetController()->SetControlRotation(resultRot);
}

