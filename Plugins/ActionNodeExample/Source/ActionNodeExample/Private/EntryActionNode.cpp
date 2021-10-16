// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryActionNode.h"

#include "ActionNodeLogs.h"
#include "ActionNode.h"


void UEntryActionNode::Execute()
{
	UE_LOG(LogTemp, Log, TEXT("UEntryActionNode::Execute"));
	OnActionNodeFinished.ExecuteIfBound();
}

UActionNode* UEntryActionNode::CreateNextActionNode()
{
	if (ActionData.Next.Num() < 1) return nullptr;
	
	return CreateNextActionNodeWithNextId(ActionData.Next[0]);
}

