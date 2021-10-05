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
	FOnTickTimelineEvent OnTickTimelineEvent;
	OnTickTimelineEvent.BindDynamic(this, &ATickEntryActor::OnTickTimelineEventHandle);
	MyActorComponent->SetTickTimelineFinishedFunc(OnTickTimelineEvent);

	Super::BeginPlay();
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
