// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionNodeSubsystem.generated.h"

class UActionNode;
/**
 * 
 */
UCLASS()
class ACTIONNODEEXAMPLE_API UActionNodeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	public:
	void ExecAction(UActionNode* ActionNode);
};
