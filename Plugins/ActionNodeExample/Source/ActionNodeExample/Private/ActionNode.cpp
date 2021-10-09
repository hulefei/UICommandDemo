// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionNode.h"

#include "Engine/StreamableManager.h"

#include "ActionData.h"
#include "EntryActionNode.h"
#include "PrintActionNode.h"

#include "ActionNodeLogs.h"
#include "BranchActionNode.h"

UActionNode::UActionNode(const FObjectInitializer& ObjectInitializer)
{
	StreamableManager = MakeShareable(new FStreamableManager());
}

UActionNode* UActionNode::CreateActionNode(const FActionData ActionData, const TMap<int32, FActionData> InActionDataMap)
{
	if (ActionData.Type == FActionType::Entry)
	{
		UEntryActionNode* ActionNode = NewObject<UEntryActionNode>();
		ActionNode->Init(ActionData, InActionDataMap);
		return ActionNode;
	}
	else if (ActionData.Type == FActionType::Print)
	{
		UPrintActionNode* ActionNode = NewObject<UPrintActionNode>();
		ActionNode->Init(ActionData, InActionDataMap);
		return ActionNode;
	}
	else if (ActionData.Type == FActionType::Branch)
	{
		UBranchActionNode* ActionNode = NewObject<UBranchActionNode>();
		ActionNode->Init(ActionData, InActionDataMap);
		return ActionNode;
	}

	return nullptr;
}

void UActionNode::Init(const FActionData InActionData, const TMap<int32, FActionData> InActionDataMap)
{
	ActionData = InActionData;
	ActionDataMap = InActionDataMap;
	OnActionNodeFinished.BindStatic(&UActionNode::ExecuteNextActionNode);
}

UActionNode* UActionNode::CreateNextActionNode()
{
	if (ActionData.Next.Num() > 0)
	{
		FActionData* ActionDataPtr = ActionDataMap.Find(ActionData.Next[0]);
		if (ActionDataPtr != nullptr)
		{
			const FActionData NextActionData = *ActionDataPtr;
			return UActionNode::CreateActionNode(NextActionData, ActionDataMap);
		}
	}

	return nullptr;
}

void UActionNode::ExecuteNextActionNode(UActionNode* NextActionNode)
{
	if (NextActionNode != nullptr)
	{
		NextActionNode->Execute();
	} else
	{
		UE_LOG(LogActionNode, Log, TEXT("Action Node End"));		
	}
}
