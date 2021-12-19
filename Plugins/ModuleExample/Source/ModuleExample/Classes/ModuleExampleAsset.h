// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ModuleExampleAsset.generated.h"

/**
 * 
 */
UCLASS()
class MODULEEXAMPLE_API UModuleExampleAsset : public UObject
{
	GENERATED_BODY()
public:
	FString Name;

#if WITH_EDITOR
	int32 Age;
#endif
	
};
