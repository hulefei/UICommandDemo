// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tickable.h"
#include "TickTimeline.generated.h"

/**
 * 
 */
UCLASS()
class TICKEXAMPLE_API UTickTimeline : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override {RETURN_QUICK_DECLARE_CYCLE_STAT(threadname, STATGROUP_Tickables);}
	// End FTickableGameObject Interface.
};
