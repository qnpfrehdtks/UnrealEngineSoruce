// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Component\InteractComponent.h"
#include "Components/SphereComponent.h"
#include "Interface/Interactive.h"
#include "Actor/interactiveActorBase.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractComponent::FindClosestInteractObject(TArray<AActor*>& arr)
{
	float prevMaxDist = 99999.0f;
	AInteractiveActorBase* resultActor = nullptr;

	// ���� ����� �������� �������� �Լ��Դϴ�.
	// ����� ���͵��� �迭�� ���������� ���鼭 ���� ����� ���͸� �����ɴϴ�.
	for (auto& actor : arr)
	{
		AInteractiveActorBase* interactItem = Cast<AInteractiveActorBase>(actor);
		if (interactItem == nullptr) continue;

		float dist = (interactItem->GetActorLocation() - GetOwner()->GetActorLocation()).Size();

		if (dist < prevMaxDist)
		{
			prevMaxDist = dist;
			resultActor = interactItem;
		}
	}

	if (resultActor != nullptr)
	{
		closestInteractObject = resultActor;
	}
	else
	{
		closestInteractObject = nullptr;
	}
}

bool UInteractComponent::InteractToObject()
{
	if (closestInteractObject != nullptr)
	{
		IInteractive::Execute_OnStartInteractive(closestInteractObject, GetOwner());
		return true;
	}


	return false;
}


