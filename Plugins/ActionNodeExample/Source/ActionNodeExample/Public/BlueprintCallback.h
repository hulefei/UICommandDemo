// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BlueprintCallback.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintThreadSafe))
class ACTIONNODEEXAMPLE_API UBlueprintCallback : public UObject
{
	GENERATED_BODY()

public:
	// ~Core
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool BranchFunction(FName EventName);
};
