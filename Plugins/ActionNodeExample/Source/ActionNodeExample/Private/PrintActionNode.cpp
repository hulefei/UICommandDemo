// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintActionNode.h"

#include "ActionNodeLogs.h"

void UPrintActionNode::Execute()
{
	UE_LOG(LogActionNode, Log, TEXT("UPrintActionNode::Execute: %s"), *ActionData.Name.ToString());
	OnActionNodeFinished.ExecuteIfBound();
}

UActionNode* UPrintActionNode::CreateNextActionNode()
{
	if (ActionData.Next.Num() < 1) return nullptr;
	
	return CreateNextActionNodeWithNextId(ActionData.Next[0]);
}