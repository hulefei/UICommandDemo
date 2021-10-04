// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TickTimeline.generated.h"

USTRUCT()
struct FTickTimeline
{
	GENERATED_USTRUCT_BODY()

private:
	/** Whether timeline should loop when it reaches the end, or stop */
	UPROPERTY()
	uint8 bLooping:1;

	/** If playback should move the current position backwards instead of forwards */
	UPROPERTY()
	uint8 bReversePlayback:1;

public:
	FTickTimeline()
		: bLooping(false)
		, bReversePlayback(false)
	{
	}

	void TickTimeline(float DeltaTime);
};
