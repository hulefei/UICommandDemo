// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimeline.h"

void FTickTimeline::TickTimeline(float DeltaTime)
{
	UE_LOG(LogTemp, Log, TEXT("FTickTimeline::TickTimeline:%f"), DeltaTime);
}
