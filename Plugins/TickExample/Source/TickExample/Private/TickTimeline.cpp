// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimeline.h"

void UTickTimeline::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Log, TEXT("DeltaTime:%f"), DeltaTime);
}

bool UTickTimeline::IsTickable() const
{
	return FTickableGameObject::IsTickable();
}
