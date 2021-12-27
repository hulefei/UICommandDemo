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
	UPROPERTY(EditAnywhere, Category=Reflection, meta=(kskill))
	int32 Age;

	UPROPERTY(EditAnywhere, Category=Reflection, meta=(kskill))
	FName Name;

	UPROPERTY(EditAnywhere, Category=Reflection, meta=(kskill))
	FString Description;

	UPROPERTY(EditAnywhere)
	FSoftObjectPath SoftObjectPath;

};
