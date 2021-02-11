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

bool AWeaponItemBase::OnCheckHit(UStateBase* state )
{
	FVector topSocketPosition = FVector::ZeroVector;
	FVector bottomSocketPosition = FVector::ZeroVector;
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

	//FRotator rot =  UKismetMathLibrary::FindLookAtRotation(topSocketPosition, bottomSocketPosition);

	FVector dir = (topSocketPosition - bottomSocketPosition).GetUnsafeNormal();
	FRotator rot = UKismetMathLibrary::MakeRotFromZ(dir);

	FCollisionQueryParams param(NAME_None, false, GetOwner());
	FCollisionResponseParams responsParam;

	FCollisionShape shape = FCollisionShape::MakeCapsule(Radius, (topSocketPosition - bottomSocketPosition).Size() * 0.5f);

	TArray<FHitResult> hitResultArray;
	bool isHit = GetWorld()->SweepMultiByChannel(hitResultArray, topSocketPosition, bottomSocketPosition, rot.Quaternion(), ECollisionChannel::ECC_Pawn, shape, param);

	if (isHit)
	{
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
						if (attackable->Execute_OnDamaged(hitActor, GetOwner(), damage, result.ImpactPoint, dir, state->attackType))
						{
							OnHitDelegate.Broadcast(GetOwner(), hitActor);

							if (HitEffect)
							{
								UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f); //Global slow motion.

								GetWorld()->GetTimerManager().SetTimer(
									timerHandler, this, 
									&AWeaponItemBase::ResetTimer,
									0.05f,false);

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
