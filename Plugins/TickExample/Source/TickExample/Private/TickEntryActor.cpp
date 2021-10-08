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
	
	FOnTickTimelineEvent OnTickTimelineEvent;
	OnTickTimelineEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineEventHandle);

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


void ATickEntryActor::OnTickTimelineEventHandle()
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineEventHandle"));
}

void ATickEntryActor::OnTickTimelineFinishedEventHandle()
{
	UE_LOG(LogTemp, Log, TEXT("ATickEntryActor::OnTickTimelineFinishedEventHandle"));
}