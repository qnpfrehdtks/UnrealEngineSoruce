// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterAnimInstance.h"
#include "Actor/LowpolyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/EquipmentComponent.h"
UCharacterAnimInstance::UCharacterAnimInstance()
{
	moveSpeed = 0.0f;
	moveDirection = 0.0f;
	bIsFalling = false;
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	APawn* pawn = TryGetPawnOwner();

	if (pawn)
	{
		myCharacter = Cast<ALowpolyCharacter>(pawn);
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* pawn =  TryGetPawnOwner();

	if (pawn)
	{
		ALowpolyCharacter* character =Cast<ALowpolyCharacter>(pawn);

		if (character)
		{
			FVector vel = character->GetVelocity();
			
			moveSpeed = FVector::DotProduct(vel, character->GetActorForwardVector());
			moveDirection = FVector::DotProduct(vel, character->GetActorRightVector());
			bIsFalling = character->GetCharacterMovement()->IsFalling();

			if (character->EquipComponent != nullptr && character->EquipComponent->GetEquippedItem(EItemEquipmentType::EIT_RightHand) != nullptr)
			{
				bIsEquippedItem = true;
			}
			else
			{
				bIsEquippedItem = false;
			}
		}
	}
}
