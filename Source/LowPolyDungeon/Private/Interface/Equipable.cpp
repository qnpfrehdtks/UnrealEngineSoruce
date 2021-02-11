// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/Equipable.h"

// Add default functionality here for any IEquipable functions that are not pure virtual.
IEquipable::IEquipable()
{

}

void IEquipable::OnEquip_Implementation( USkeletalMeshComponent* mesh)
{
}

void IEquipable::OnEquip_EquipType_Implementation(USkeletalMeshComponent* mesh, FName SocketName)
{
}

void IEquipable::OnDetach_Implementation()
{
}
