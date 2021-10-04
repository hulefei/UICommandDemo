// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionNodeSubsystem.h"

#include "ActionNode.h"
#include "BranchActionNode.h"

void UActionNodeSubsystem::ExecAction(UActionNode* ActionNode)
{
	const auto BranchActionNode = Cast<UBranchActionNode>(ActionNode);
	if (BranchActionNode != nullptr)
	{
		BranchActionNode->Execute();
	} else
	{
		UE_LOG(LogTemp, Log, TEXT("ActionNode not Support"));
	}
}
