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

	MyActorComponent->ResetTimeline(100);
	
	FOnTickTimelineUpdateEvent OnTickTimelineUpdateEvent;
	OnTickTimelineUpdateEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineUpdateEventHandle);

	FOnTickTimelineEvent OnTickTimelineFinishedEvent;
	OnTickTimelineFinishedEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineFinishedEventHandle);

	FOnTickTimelineKeyframeEvent OnTickTimelineKeyframeEvent;
	OnTickTimelineKeyframeEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineKeyframeEventHandle);
	
	MyActorComponent->SetTickTimelineFinishedFunc(OnTickTimelineFinishedEvent);
	MyActorComponent->SetTickTimelinePostUpdateFunc(OnTickTimelineUpdateEvent);
	MyActorComponent->AddEvent(FName(TEXT("TestEvent1")), 50, OnTickTimelineKeyframeEvent);

	MyActorComponent->PlayFromStart();
}

// Called every frame
void ATickEntryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATickEntryActor::OnTickTimelineUpdateEventHandle(int32 Position)
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineUpdateEventHandle:%d"), Position);
}

void ATickEntryActor::OnTickTimelineFinishedEventHandle()
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineFinishedEventHandle"));
}

void ATickEntryActor::OnTickTimelineEventHandle()
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineEventHandle: 50"));
}

void ATickEntryActor::OnTickTimelineKeyframeEventHandle(FName Name)
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineKeyframeEventHandle: %s"), *Name.ToString());
}