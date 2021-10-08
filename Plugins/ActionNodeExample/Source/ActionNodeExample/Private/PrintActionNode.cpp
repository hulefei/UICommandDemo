// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintActionNode.h"

DEFINE_LOG_CATEGORY_STATIC(LogActionNode, Log, All)

void UPrintActionNode::Execute()
{
	UE_LOG(LogActionNode, Log, TEXT("UPrintActionNode::Execute: %s"), *ActionData.Name.ToString());
	UActionNode* NextActionNode = CreateNextActionNode();
	OnActionNodeFinished.ExecuteIfBound(NextActionNode);
}