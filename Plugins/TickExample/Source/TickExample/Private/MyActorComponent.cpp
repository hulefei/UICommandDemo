// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "MyBaseActor.h"

UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMyActorComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UMyActorComponent::Deactivate()
{
	Super::Deactivate();
	PrimaryComponentTick.SetTickFunctionEnable(false);
}

void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	const FActorSpawnParameters Parameters;
	MyBaseActor = GetWorld()->SpawnActor<AMyBaseActor>(ActorBlueprint, Parameters);
}

void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickTimeline.TimelineTick(DeltaTime);
}

void UMyActorComponent::ResetTimeline(const int32 InFrameNum, const bool InbLooping)
{
	TickTimeline.Reset(InFrameNum);
}

void UMyActorComponent::Play()
{
	Activate();
	TickTimeline.Play();
}

void UMyActorComponent::PlayFromStart()
{
	Activate();
	TickTimeline.PlayFromStart();
}

void UMyActorComponent::Stop()
{
	Deactivate();
	TickTimeline.Stop();
}

void UMyActorComponent::SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc)
{
	TickTimeline.SetTickTimelineFinishedFunc(NewTickTimelineFinishedFunc);
}

void UMyActorComponent::SetTickTimelinePostUpdateFunc(FOnTickTimelineEvent NewTimelinePostUpdateFunc)
{
	TickTimeline.SetTimelinePostUpdateFunc(NewTimelinePostUpdateFunc);
}
