// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionNode.h"

#include "BranchActionNode.generated.h"

class ABridgeActor;
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

	UPROPERTY()
	ABridgeActor* BridgeActor;

protected:
	virtual UActionNode* CreateNextActionNode() override;
	
private:
	int32 NextIndex = -1;
};
