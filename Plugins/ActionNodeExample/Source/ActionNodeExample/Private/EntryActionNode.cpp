// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryActionNode.h"

#include "ActionData.h"
#include "ActionNode.h"

DEFINE_LOG_CATEGORY_STATIC(LogActionNode, Log, All)

void UEntryActionNode::Execute()
{
	UE_LOG(LogActionNode, Log, TEXT("UEntryActionNode::Execute"));
	UActionNode* NextActionNode = CreateNextActionNode();
	OnActionNodeFinished.ExecuteIfBound(NextActionNode);
}
