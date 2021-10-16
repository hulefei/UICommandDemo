// Fill out your copyright notice in the Description page of Project Settings.


#include "BranchActionNode.h"

#include "ActionNodeLogs.h"
#include "BlueprintCallback.h"

#include "Engine/StreamableManager.h"

void UBranchActionNode::Init(const FActionData InActionData, const TMap<int32, FActionData> InActionDataMap)
{
	Super::Init(InActionData, InActionDataMap);
	
	const FSoftObjectPath BlueprintReference(TEXT("Blueprint'/Game/Skill_BP.Skill_BP'"));
	UBlueprint* ActionBlueprint = Cast<UBlueprint>(StreamableManager->LoadSynchronous(BlueprintReference));
	if (ActionBlueprint->GeneratedClass->IsChildOf(UBlueprintCallback::StaticClass()))
	{
		//TODO: 可进行缓存优化
		BlueprintCallback = NewObject<UBlueprintCallback>(
		GetTransientPackage(), ActionBlueprint->GeneratedClass);
	}
	else
	{
		UE_LOG(LogActionNode, Error, TEXT("Not ChildOf UBlueprintCallback:[%s]"),
		       *BlueprintReference.GetAssetPathString());
	}
}

void UBranchActionNode::Execute()
{
	//根据返回值 创建 CreateNextActionNode
	UE_LOG(LogActionNode, Log, TEXT("UBranchActionNode::Execute"));
	if (BlueprintCallback != nullptr)
	{
		BranchResult = BlueprintCallback->BranchFunction(ActionData.Name);
	}
	else
	{
		UE_LOG(LogActionNode, Error, TEXT("BlueprintCallback != nullptr"));
	}
	
	OnActionNodeFinished.ExecuteIfBound();
}

UActionNode* UBranchActionNode::CreateNextActionNode()
{
	const int32 NextIndex = BranchResult ? 0 : 1;
	
	if (NextIndex < 0 || NextIndex >= ActionData.Next.Num()) return nullptr;

	const int32 NextId = ActionData.Next[NextIndex];
	return CreateNextActionNodeWithNextId(NextId);
}
