// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionNode.h"

#include "PrintActionNode.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONNODEEXAMPLE_API UPrintActionNode : public UActionNode
{
	GENERATED_BODY()

	public:
	virtual void Execute() override;
	virtual UActionNode* CreateNextActionNode() override;
};
