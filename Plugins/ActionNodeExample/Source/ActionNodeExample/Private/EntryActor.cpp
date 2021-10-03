// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryActor.h"

#include "ActionNodeSubsystem.h"
#include "BranchActionNode.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEntryActor::AEntryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEntryActor::BeginPlay()
{
	Super::BeginPlay();

	// UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	// UActionNodeSubsystem* ActionNodeSubsystem = GameInstance->GetSubsystem<UActionNodeSubsystem>();
	// UBranchActionNode* BranchActionNode = NewObject<UBranchActionNode>(this);
	// BranchActionNode->Init();
	// ActionNodeSubsystem->ExecAction(BranchActionNode);

	// auto StreamableManager = new FStreamableManager();
	// const FStringAssetReference BlueprintReference(TEXT("Blueprint'/Game/BridgeActor_BP.BridgeActor_BP'"));
	// auto ActionBlueprint = Cast<UBlueprint>(StreamableManager->LoadSynchronous(BlueprintReference));
	const FVector Location(-3000, -3000, -3000);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	
	auto xBridgeActor = GetWorld()->SpawnActor<ABridgeActor>(
		BridgeActor, Location, FRotator::ZeroRotator, SpawnParams);
	if (xBridgeActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("xBridgeActor == nullptr"));
	} else
	{
		UE_LOG(LogTemp, Log, TEXT("xBridgeActor != nullptr"));
	}
}

// Called every frame
void AEntryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

