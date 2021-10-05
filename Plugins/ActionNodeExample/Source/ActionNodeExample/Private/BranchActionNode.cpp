// Fill out your copyright notice in the Description page of Project Settings.


#include "BranchActionNode.h"

#include "BridgeActor.h"
#include "Engine/StreamableManager.h"

void UBranchActionNode::Init()
{
	const FStringAssetReference BlueprintReference(TEXT("Blueprint'/Game/BridgeActor_BP.BridgeActor_BP'"));
	ActionBlueprint = Cast<UBlueprint>(StreamableManager->LoadSynchronous(BlueprintReference));
	// auto BlueprintClass = ActionBlueprint->GetBlueprintClass();
	const FVector Location(-3000, -3000, -3000);
	const FActorSpawnParameters SpawnParams;
	//TODO
	BridgeActor = GetWorld()->SpawnActor<ABridgeActor>(
		ActionBlueprint->GeneratedClass, Location, FRotator::ZeroRotator, SpawnParams);

	OnActionNodeFinished.BindLambda([](UActionNode* ActionNode)-> void
	{
		if (ActionNode != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("ActionNode != nullptr"));
		} else
		{
			UE_LOG(LogTemp, Log, TEXT("ActionNode == nullptr"));
		}
	});
}

void UBranchActionNode::Deinitialization()
{
	OnActionNodeFinished.Unbind();
}

void UBranchActionNode::Execute()
{
	check(BridgeActor)
	int32 NextIndex = -1;
	UActionNode* ActionNode = nullptr;
	if (BridgeActor->DispatchEvent(FName(TEXT("test2")), NextIndex))
	{
		ActionNode = NewObject<UActionNode>();
	}
	OnActionNodeFinished.ExecuteIfBound(ActionNode);
}
