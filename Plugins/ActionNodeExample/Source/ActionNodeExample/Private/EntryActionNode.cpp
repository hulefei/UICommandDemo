// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryActionNode.h"

#include "ActionNode.h"


void UEntryActionNode::Execute()
{
	UE_LOG(LogTemp, Log, TEXT("UEntryActionNode::Execute"));
	UActionNode* NextActionNode = CreateNextActionNode();
	OnActionNodeFinished.ExecuteIfBound(NextActionNode);
}
