// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionNode.h"

#include "BranchActionNode.generated.h"

class UBlueprintCallback;
class UBlueprint;
/**
 * 
 */
UCLASS()
class ACTIONNODEEXAMPLE_API UBranchActionNode : public UActionNode
{
	GENERATED_BODY()

public:
	virtual void Execute() override;
	virtual void Init(const FActionData InActionData, const TMap<int32, FActionData> InActionDataMap) override;

protected:
	virtual UActionNode* CreateNextActionNode() override;
	
private:
	bool BranchResult = false;

	UPROPERTY()
	UBlueprintCallback* BlueprintCallback = nullptr;
};
