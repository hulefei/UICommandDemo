// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DetailObject.generated.h"

/**
 * 
 */
UCLASS()
class DETAILVIEWEXAMPLE_API UDetailObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="DetailView")
	int32 Age;
};
