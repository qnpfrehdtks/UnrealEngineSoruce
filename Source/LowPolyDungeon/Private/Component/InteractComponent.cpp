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
//	interactHitCollsion->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnHitCollisionToItem);
	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractComponent::FindClosestInteractObject(TArray<AActor*>& arr)
{
	float prevMaxDist = 99999.0f;
	AInteractiveActorBase* resultActor = nullptr;

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
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Select!!"));
		//IInteractive::Execute_OnStartInteractive(InteractObject, GetOwner());
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

//void UInteractComponent::OnHitCollisionToItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	IInteractive* interactItem = Cast<IInteractive>(OtherActor);
//	UE_LOG(LogTemp, Warning, TEXT("Interact : %s"), *OtherActor->GetName());
//	if (interactItem != nullptr)
//	{
//		float MaxDist = 99999.0f;
//		TArray<AActor*> arrOverlapping;
//		
//		//interactHitCollsion->GetOverlappingActors(arrOverlapping);
//
//		for (auto& actor : arrOverlapping)
//		{
//			float dist = (actor->GetActorLocation() - GetOwner()->GetActorLocation()).Size();
//
//		//	if (dist < MaxDist)
//		//	{
//				MaxDist = dist;
//				UE_LOG(LogTemp, Warning,  TEXT("Interact : %s"), *actor->GetName());
//				InteractObject = Cast<AInteractiveActorBase>(actor);
//
//				IInteractive::Execute_OnStartInteractive(InteractObject, GetOwner());
//		//	}
//		}
//	}
//
//}

