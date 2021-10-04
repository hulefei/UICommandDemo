﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseActor.h"


AMyBaseActor::AMyBaseActor(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComp"));
	MyActorComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMyBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

