// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionExecutor.h"

#include "ActionNode.h"
#include "EntryActionNode.h"

bool UActionExecutor::Execute() const
{
	auto EntryAction = Cast<UEntryActionNode>(UActionNode::CreateActionNode(Entry, ActionDataMap));
	if (EntryAction != nullptr)
	{
		EntryAction->Execute();
		return true;
	}

	return false;
}

void UActionExecutor::Init(const FActionData InEntry, const TMap<int32, FActionData> InActionDataMap)
{
	Entry = InEntry;
	ActionDataMap = InActionDataMap;
}