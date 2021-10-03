// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionNode.generated.h"

struct FStreamableManager;
/**
 * 
 */
UCLASS()
class ACTIONNODEEXAMPLE_API UActionNode : public UObject
{
	GENERATED_BODY()

	public:
	explicit UActionNode(const FObjectInitializer& ObjectInitializer);
	public:
	virtual void Execute() {};

	FStreamableManager* StreamableManager = nullptr;
};
