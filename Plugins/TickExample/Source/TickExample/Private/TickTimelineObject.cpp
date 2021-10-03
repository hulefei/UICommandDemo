// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimelineObject.h"
#include "Containers/Ticker.h"

void UTickTimelineObject::Start()
{
	// MyTickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UTickTimelineObject::Tick));	
}

bool UTickTimelineObject::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("UTickTimelineObject Tick, %f."), DeltaTime);
	return true;
}
