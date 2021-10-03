// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeActor.h"


// Sets default values
ABridgeActor::ABridgeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABridgeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABridgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABridgeActor::DispatchEvent_Implementation(FName EventName)
{
	UE_LOG(LogTemp, Log, TEXT("DispatchEvent not Implementation "));
}

