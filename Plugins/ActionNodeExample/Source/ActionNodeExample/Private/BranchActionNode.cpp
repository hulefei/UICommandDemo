// Fill out your copyright notice in the Description page of Project Settings.


#include "BranchActionNode.h"

#include "BridgeActor.h"
#include "Engine/StreamableManager.h"

void UBranchActionNode::Init()
{
	// const FStringAssetReference BlueprintReference(TEXT("Blueprint'/Game/BridgeActor_BP.BridgeActor_BP'"));
	// ActionBlueprint = Cast<UBlueprint>(StreamableManager->LoadSynchronous(BlueprintReference));
	// auto BlueprintClass = ActionBlueprint->GetBlueprintClass();
	// const FVector Location(-3000, -3000, -3000);
	// const FActorSpawnParameters SpawnParams;
	// auto xBridgeActor = GetWorld()->SpawnActor<AActor>(
	// 	BlueprintClass, Location, FRotator::ZeroRotator, SpawnParams);
	// if (xBridgeActor == nullptr)
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("xBridgeActor == nullptr"));
	// } else
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("xBridgeActor != nullptr"));
	// }
}
//
// UBranchActionNode::UBranchActionNode(const FObjectInitializer& ObjectInitializer)
// {
// 	// Super(ObjectInitializer);
// 	// static ConstructorHelpers::FClassFinder<ABridgeActor> BridgeActor(TEXT("/Game/BridgeActor_BP")); // 这个就不能右键该资源 Copy Reference，只能是不带name的一个路径
// 	// if (BridgeActor.Succeeded())
// 	// {
// 	// 	UE_LOG(LogTemp, Warning, TEXT("--- BridgeActor.Succeeded()"));
// 	// 	// mCDComp = NewObject<ABridgeActor>(this, CDComplAsset.Class, "UCoolDownComp"); //必须提供一个 name（UCoolDownComp）
// 	// 	// mCDComp->SetupAttachment(RootComponent);
// 	// 	const FVector Location(-3000, -3000, -3000);
// 	// 	const FActorSpawnParameters SpawnParams;
// 	// 	auto xBridgeActor = GetWorld()->SpawnActor<AActor>(
// 	// 		BridgeActor.Class, Location, FRotator::ZeroRotator, SpawnParams);
// 	// }
// }

void UBranchActionNode::Execute()
{
	Super::Execute();

	// check(BridgeActor)
	// BridgeActor->DispatchEvent(FName(TEXT("test1")));
}
