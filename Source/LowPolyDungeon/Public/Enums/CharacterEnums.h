// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEnums.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Walk UMETA(DisplayName = "Walk"),
	ECS_Sprint UMETA(DisplayName = "Sprint"),
	ECS_Idle UMETA(DisplayName = "Idle"),

	ECS_Dodge UMETA(DisplayName = "Dodge"),
	ECS_BackStep UMETA(DisplayName = "BackStep"),
	ECS_DashAttack UMETA(DisplayName = "DashAttack"),

	ECS_Attack1 UMETA(DisplayName = "Attack1"),
	ECS_Attack2 UMETA(DisplayName = "Attack2"),
	ECS_Attack3 UMETA(DisplayName = "Attack3"),
	ECS_Attack4 UMETA(DisplayName = "Attack4"),
	ECS_Attack5 UMETA(DisplayName = "Attack5"),
	ECS_Attack6 UMETA(DisplayName = "Attack6"),

	ECS_Falling UMETA(DisplayName = "Falling"),
	ECS_Block UMETA(DisplayName = "Block"),

	ECS_LightStun UMETA(DisplayName = "Light_Stun"),
	ECS_StrongStun UMETA(DisplayName = "Strong_Stun"),

	ECS_KnockDown UMETA(DisplayName = "KnockDown"),

	ECS_Drink UMETA(DisplayName = "Drink"),
	ECS_Dead UMETA(DisplayName = "Dead"),

	ECS_Blocking UMETA(DisplayName = "Blocking"),

	ECS_HeavyAttack1 UMETA(DisplayName = "HeavyAttack1"),
	ECS_HeavyAttack2 UMETA(DisplayName = "HeavyAttack2"),

	ECS_EquipChange UMETA(DisplayName = "EquipChange"),

	ECS_Max UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class ECharacterPhase : uint8
{
	ECP_NONE UMETA(DisplayName = "None"),
	ECP_PHASE_01 UMETA(DisplayName = "Phase1"),
	ECP_PHASE_02 UMETA(DisplayName = "Phase2"),
	ECP_Max UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	ECT_NONE UMETA(DisplayName = "None"),
	ECT_Normal UMETA(DisplayName = "Normal"),
	ECT_Boss UMETA(DisplayName = "Boss"),
	ECT_Player UMETA(DisplayName = "Character"),
	ECT_Max UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	EAT_NONE UMETA(DisplayName = "None"),
	EAT_NoStun UMETA(DisplayName = "NoStun"),
	EAT_LightStun UMETA(DisplayName = "LightStun"),
	EAT_StrongStun UMETA(DisplayName = "StrongStun"),
	EAT_KnockDown UMETA(DisplayName = "KnockDown"),
	EAT_Max UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class ECharacterHitArmor : uint8
{
	EAT_NONE UMETA(DisplayName = "None"),
	EAT_NoStun UMETA(DisplayName = "Strong_Immune"),
	EAT_LightImmume UMETA(DisplayName = "Light_Immune"),
	EAT_StrongImmume UMETA(DisplayName = "Strong_Immune"),
	ECH_AllImmune UMETA(DisplayName = "All_Immune"),
	EAT_Max UMETA(DisplayName = "Max"),
};


