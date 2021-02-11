// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Interactive.h"
#include "InteractComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractToItemDelegate, EInteractiveType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOWPOLYDUNGEON_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void FindClosestInteractObject(TArray<AActor*>& arr);

	UFUNCTION()
	bool InteractToObject();

	FOnInteractToItemDelegate OnInteractDelegate;
		
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class AInteractiveActorBase* InteractObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class AInteractiveActorBase* closestInteractObject;
	
};
