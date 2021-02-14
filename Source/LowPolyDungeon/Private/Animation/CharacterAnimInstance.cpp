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
			/* 캐릭터의 벨로시티값을 가져온다. */
			FVector vel = character->GetVelocity();
			
			/* 인터넷 조사한 바로는 이 값을 통해 -1 ~ 1 사이의 캐릭터가 어느 방향으로 움직였는지 결과값을 구해온다. */
			moveSpeed = FVector::DotProduct(vel, character->GetActorForwardVector());
			moveDirection = FVector::DotProduct(vel, character->GetActorRightVector());
			bIsFalling = character->GetCharacterMovement()->IsFalling();
			/* 이를 통해 캐릭터의 블렌드 스페이스의 애니메이션에 영향을 줌. */
			
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
