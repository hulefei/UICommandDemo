// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionNode.h"

#include "EntryActionNode.generated.h"

struct FActionData;

/**
 * 
 */

UCLASS()
class ACTIONNODEEXAMPLE_API UEntryActionNode : public UActionNode
{
	GENERATED_BODY()

public:
	virtual void Execute() override;
	virtual UActionNode* CreateNextActionNode() override;
};
