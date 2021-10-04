// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

#include "MyBaseActor.h"


// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMyActorComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	UTickTimelineComponent* TickTimelineComponent = CreateDefaultSubobject<UTickTimelineComponent>(TEXT("TickTimelineComp"));
	TickTimelineComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	// const FVector Location(-3000, -3000, -3000);
	// const FActorSpawnParameters SpawnParams;
	// MyBaseActor = GetWorld()->SpawnActor<AMyBaseActor>(
	// 	ActorBlueprint, Location, FRotator::ZeroRotator, SpawnParams);

	// TickTimelineComponent = CreateDefaultSubobject<UTickTimelineComponent>(TEXT("TickTimeline"));
}

// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickTimeline.TickTimeline(DeltaTime);
}

