// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomAsset.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMASSET_API UCustomAsset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=NewAsset)
	FText Value;
};
