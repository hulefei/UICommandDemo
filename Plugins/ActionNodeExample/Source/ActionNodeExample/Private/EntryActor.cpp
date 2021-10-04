// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryActor.h"

#include "ActionNodeSubsystem.h"
#include "BranchActionNode.h"
#include "BridgeActor.h"
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

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UActionNodeSubsystem* ActionNodeSubsystem = GameInstance->GetSubsystem<UActionNodeSubsystem>();
	UBranchActionNode* BranchActionNode = NewObject<UBranchActionNode>(this);
	BranchActionNode->Init();
	ActionNodeSubsystem->ExecAction(BranchActionNode);
}

// Called every frame
void AEntryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

