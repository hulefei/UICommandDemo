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
	BridgeActor = GetWorld()->SpawnActor<ABridgeActor>(
		ActionBlueprint->GeneratedClass, Location, FRotator::ZeroRotator, SpawnParams);
}

void UBranchActionNode::Execute()
{
	check(BridgeActor)
	const int32 NextIndex = BridgeActor->DispatchEvent(FName(TEXT("test2")));
	UE_LOG(LogTemp, Log, TEXT("NextIndex:%d"), NextIndex);
}
