// Fill out your copyright notice in the Description page of Project Settings.


#include "BranchActionNode.h"

#include "BridgeActor.h"
#include "Engine/StreamableManager.h"

void UBranchActionNode::Init(const FActionData InActionData, const TMap<int32, FActionData> InActionDataMap)
{
	Super::Init(InActionData, InActionDataMap);
	
	// const FStringAssetReference BlueprintReference(TEXT("Blueprint'/Game/BridgeActor_BP.BridgeActor_BP'"));
	const FStringAssetReference BlueprintReference(TEXT("Blueprint'/Game/BridgeActor_BP.BridgeActor_BP'"));

	const int32 HashKey = GetTypeHash(InActionData.AssetReferenceString);
	ABridgeActor** BridgeActorPtr = BridgeActorMap.Find(HashKey);
	if (BridgeActorPtr != nullptr)
	{
		BridgeActor = *BridgeActorPtr;
	} else
	{
		UBlueprint* ActionBlueprint = Cast<UBlueprint>(StreamableManager->LoadSynchronous(BlueprintReference));
		// auto BlueprintClass = ActionBlueprint->GetBlueprintClass();
		const FVector Location(-3000, -3000, -3000);
		const FActorSpawnParameters SpawnParams;
		BridgeActor = GetWorld()->SpawnActor<ABridgeActor>(
			ActionBlueprint->GeneratedClass, Location, FRotator::ZeroRotator, SpawnParams);

		BridgeActorMap.Add(HashKey, BridgeActor);
	}
}

void UBranchActionNode::Execute()
{
	//TODO: 更具返回值 创建 CreateNextActionNode
	check(BridgeActor)
	
	BridgeActor->DispatchEvent(FName(TEXT("test2")), NextIndex);
	// UActionNode* ActionNode = nullptr;
	// if (BridgeActor->DispatchEvent(FName(TEXT("test2")), NextIndex))
	// {
	// 	ActionNode = NewObject<UActionNode>();
	// }

	UActionNode* NextActionNode = CreateNextActionNode();
	OnActionNodeFinished.ExecuteIfBound(NextActionNode);
}

UActionNode* UBranchActionNode::CreateNextActionNode()
{
	if (NextIndex < 0 || NextIndex >= ActionData.Next.Num()) return nullptr;

	ActionData.Next[NextIndex];
	
}
