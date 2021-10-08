// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionData.h"
#include "UObject/Object.h"
#include "ActionNode.generated.h"

struct FStreamableManager;
class UActionNode;
DECLARE_DELEGATE_OneParam(FOnActionNodeFinished, UActionNode*)
/**
 * 
 */

UCLASS()
class ACTIONNODEEXAMPLE_API UActionNode : public UObject
{
	GENERATED_BODY()

public:
	explicit UActionNode(const FObjectInitializer& ObjectInitializer);
	
	virtual void Execute() { };
	virtual void Init(const FActionData InActionData, const TMap<int32, FActionData> InActionDataMap);
	
	static UActionNode* CreateActionNode(const FActionData ActionData, const TMap<int32, FActionData> InActionDataMap);

	TSharedPtr<FStreamableManager> StreamableManager;

protected:
	
	virtual UActionNode* CreateNextActionNode();

	static void ExecuteNextActionNode(UActionNode* NextActionNode);
	
	FOnActionNodeFinished OnActionNodeFinished;

	FActionData ActionData;
	TMap<int32, FActionData> ActionDataMap;

	
};
