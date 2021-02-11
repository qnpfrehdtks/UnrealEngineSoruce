// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/Interactive.h"

// Add default functionality here for any IInteractive functions that are not pure virtual.

IInteractive::IInteractive()
{

}

bool IInteractive::OnStartInteractive_Implementation(AActor* actor)
{
	return true;
}
