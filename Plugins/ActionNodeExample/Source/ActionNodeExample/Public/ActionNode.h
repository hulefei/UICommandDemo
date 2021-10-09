// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionData.h"
#include "BridgeActor.h"
#include "UObject/Object.h"

#include "ActionNode.generated.h"

struct FStreamableManager;
class UActionNode;

DECLARE_DELEGATE(FOnActionNodeFinished)
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
	/** 不同类型的子类需要实现此方法实现自己查找下一个NextActionNode的逻辑 */
	virtual UActionNode* CreateNextActionNode();
	
	void ExecuteNextActionNode();
	
	/** 工具方法: 使用 NextId 来创建ActionNode */
	UActionNode* CreateNextActionNodeWithNextId(const int32 NextId);
	
	FOnActionNodeFinished OnActionNodeFinished;

	FActionData ActionData;
	//key:ActionData.Id , value:FActionData
	UPROPERTY()
	TMap<int32, FActionData> ActionDataMap;
	//key:Reference.hashId , value:ABridgeActor
	UPROPERTY()
	TMap<int32, ABridgeActor*> BridgeActorMap;
};
