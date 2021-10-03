// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEditorSubsystem.h"

void UMyEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UMyEditorSubsystem::Initialize"));
}

void UMyEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Log, TEXT("UMyEditorSubsystem::Deinitialize"));
}

void UMyEditorSubsystem::Tick(float DeltaTime)
{
	// UE_LOG(LogTemp, Log, TEXT("UMyEditorSubsystem::Tick"));
}

bool UMyEditorSubsystem::IsTickable() const
{
	return FTickableGameObject::IsTickable();
}

TStatId UMyEditorSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(threadname, STATGROUP_Tickables);
}

void UMyEditorSubsystem::AddScore(float delta)
{
}
