// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TickTimelineObject.generated.h"

/**
 * 
 */
UCLASS()
class TICKEXAMPLE_API UTickTimelineObject : public UObject
{
	GENERATED_BODY()

	public:
	FDelegateHandle MyTickerHandle;
	
	void Start();
	bool Tick(float DeltaTime);
};


