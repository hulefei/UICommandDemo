// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimelineComponent.h"


// Sets default values for this component's properties
UTickTimelineComponent::UTickTimelineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTickTimelineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTickTimelineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TheTimeline.TickTimeline(DeltaTime);
}

void UTickTimelineComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
}

void UTickTimelineComponent::Deactivate()
{
	Super::Deactivate();
}

bool UTickTimelineComponent::IsReadyForOwnerToAutoDestroy() const
{
	return Super::IsReadyForOwnerToAutoDestroy();
}

