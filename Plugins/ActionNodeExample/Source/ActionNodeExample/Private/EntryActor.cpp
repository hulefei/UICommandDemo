// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryActor.h"

#include "ActionData.h"
#include "ActionExecutor.h"


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

	EntryActionData.Id = 1;
	EntryActionData.Name = FName(TEXT("Name1"));
	EntryActionData.Type = FActionType::Entry;
	EntryActionData.Next.Add(3);

	FActionData ActionData2{};
	ActionData2.Id = 2;
	ActionData2.Name = FName(TEXT("Name2"));
	ActionData2.Type = FActionType::Print;
	ActionData2.Next.Add(3);

	FActionData ActionData3{};
	ActionData3.Id = 3;
	ActionData3.Name = FName(TEXT("Name3"));
	ActionData3.Type = FActionType::Print;

	ActionDataMap.Add(EntryActionData.Id, EntryActionData);
	ActionDataMap.Add(ActionData2.Id, ActionData2);
	ActionDataMap.Add(ActionData3.Id, ActionData3);

	UActionExecutor* ActionExecutor = UActionExecutor::New(EntryActionData, ActionDataMap);
	ActionExecutor->Execute();
}

// Called every frame
void AEntryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

