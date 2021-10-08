// Fill out your copyright notice in the Description page of Project Settings.


#include "TickEntryActor.h"
#include "MyActorComponent.h"
#include "TickEntryActor.h"


// Sets default values
ATickEntryActor::ATickEntryActor()
{
	PrimaryActorTick.bCanEverTick = true;
	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComp"));
}

// Called when the game starts or when spawned
void ATickEntryActor::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTickTimelineUpdateEvent OnTickTimelineEvent;
	OnTickTimelineEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineUpdateEventHandle);

	FOnTickTimelineEvent OnTickTimelineFinishedEvent;
	OnTickTimelineFinishedEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineFinishedEventHandle);
	
	MyActorComponent->SetTickTimelineFinishedFunc(OnTickTimelineFinishedEvent);
	MyActorComponent->SetTickTimelinePostUpdateFunc(OnTickTimelineEvent);

	MyActorComponent->ResetTimeline(100);
	MyActorComponent->PlayFromStart();
}

// Called every frame
void ATickEntryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATickEntryActor::OnTickTimelineUpdateEventHandle(int32 Position)
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineEventHandle:%d"), Position);
}

void ATickEntryActor::OnTickTimelineFinishedEventHandle()
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineFinishedEventHandle"));
}