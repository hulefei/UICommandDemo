// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TargetObject.generated.h"

/**
 * 
 */
UCLASS()
class PRESTUDYEXAMPLE_API UTargetObject : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, Category=Reflection)
	int32 Age;
	
};
