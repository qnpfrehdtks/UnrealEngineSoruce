// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WeaponItemBase.h"

#include "Camera/CameraComponent.h"
#include "Enums/CharacterEnums.h"


#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h" 

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

#include "Component/FSMComponent.h"
#include "Actor/LowPolyCharacter.h"
#include "DrawDebugHelpers.h"

#include "Particles/ParticleSystemComponent.h"
#include "State/StateBase.h"
#include "State/CombatState.h"

#include "Enums/ItemEnums.h"

#include "TimerManager.h"

const FString AWeaponItemBase::attackAttriName = FString::Printf(TEXT("attack"));
const FString AWeaponItemBase::attackRangeName = FString::Printf(TEXT("range"));

AWeaponItemBase::AWeaponItemBase()
{
}

void AWeaponItemBase::BeginPlay()
{
	Super::BeginPlay();

	AttackPoint = *itemData.mapAttribute.Find(attackAttriName);
	Radius = *itemData.mapAttribute.Find(attackRangeName);
}

void AWeaponItemBase::UseItem_Implementation(int32 index)
{
	 Super::UseItem_Implementation(index);
}

void AWeaponItemBase::ResetTimer()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}


/* 아이템 공격시 히트했나 안했나 체크하는 함수, */
bool AWeaponItemBase::OnCheckHit(UStateBase* state )
{
	FVector topSocketPosition = FVector::ZeroVector;
	FVector bottomSocketPosition = FVector::ZeroVector;

	/* 무기에 달린 TopSocket, BottomSocket의 위치값을 가져옵니다. */
	if (ItemMesh->IsVisible())
	{
		topSocketPosition = ItemMesh->GetSocketLocation(TopSocketName);
		bottomSocketPosition = ItemMesh->GetSocketLocation(BottomSocketName);
	}
	else
	{
		topSocketPosition = StaticItemMesh->GetSocketLocation(TopSocketName);
		bottomSocketPosition = StaticItemMesh->GetSocketLocation(BottomSocketName);
	}

	// Bottom 소켓에서 Top Socket까지의 방향 노말 벡터를 구함.
	// 이 노말벡터가 무기의 히트 박스를 만들때 필요한 회전을 만들때 용이함.
	FVector dir = (topSocketPosition - bottomSocketPosition).GetUnsafeNormal();
	FRotator rot = UKismetMathLibrary::MakeRotFromZ(dir);

	/* 콜리전 쿼리 파라미터 설정. */
	FCollisionQueryParams param(NAME_None, false, GetOwner());
	FCollisionResponseParams responsParam;

	/* 앞에서 구한 길이, 반지름으로 캡슐 생성 */
	FCollisionShape shape = FCollisionShape::MakeCapsule(Radius, (topSocketPosition - bottomSocketPosition).Size() * 0.5f);

	TArray<FHitResult> hitResultArray;
	/* 월드에서 Sweep함수를 이용하여 여러개의 오브젝트가 히트했는지 체크한다. */
	bool isHit = GetWorld()->SweepMultiByChannel(hitResultArray, topSocketPosition, bottomSocketPosition, rot.Quaternion(), ECollisionChannel::ECC_Pawn, shape, param);

	/* 히트 했구나 */
	if (isHit)
	{
		/* 포문 돌면서 각 액터마다 실행시킨다. */
		for (auto& result : hitResultArray)
		{
			AActor* hitActor = result.GetActor();

			if (hitActor != nullptr)
			{
				IAttackable* attackable = Cast<IAttackable>(hitActor);

				if (attackable != nullptr)
				{
					UCombatState* combatState = Cast<UCombatState>(state);

					if (combatState)
					{
						float damage = combatState->attackMult * AttackPoint;

						FDamageEvent DamageEvent;
						/* IAttackable 인터페이스를 구현받은 클래스라면 OnDamage 실행. */
						/* 만약 true인 경우는 적이 공격에 명중당했다. false인 경우는 적이 방어자세를 취해서 공격을 막았다. 적이 회피중이다. 등등 */
						if (attackable->Execute_OnDamaged(hitActor, GetOwner(), damage, result.ImpactPoint, dir, state->attackType))
						{
							/* 히트 했다는 델리게이트 함수 실행. */
							OnHitDelegate.Broadcast(GetOwner(), hitActor);

							if (HitEffect)
							{
								/* 약간의 슬로우 타임을 주어 타격감을 준다. */
								UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f); //Global slow motion.

								/* 타이머 돌려서 시간을 원상태로 돌린다. */
								GetWorld()->GetTimerManager().SetTimer(
									timerHandler, this, 
									&AWeaponItemBase::ResetTimer,
									0.05f,false);

								/* 맞은 자리에 히트 이펙트 실행. */
								auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, result.ImpactPoint, FRotator::ZeroRotator, true);
								particle->SetRelativeScale3D(FVector(0.35f, 0.35f, 0.35f));

								
							}

							return true;
						}
					}
				}
			}
		}

		return false;
	}
	//	DrawDebugCapsule(GetWorld(), (topSocketPosition + bottomSocketPosition) * 0.5f, shape.Capsule.HalfHeight, Radius, rot.Quaternion(), FColor::Red, false, 2.0f);
	//	DrawDebugSphere(GetWorld(), (topSocketPosition + bottomSocketPosition) * 0.5f, 30.0f, 3, FColor::Red, false, 2.0f);
	return false;


}
