// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include "KSkillAsset.h"
#include "KSkillCore.h"
#include "ModuleExample.h"
#include "ModuleExampleAsset.h"


// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	FKSkillCore& KSkillCore = FModuleManager::Get().LoadModuleChecked<FKSkillCore>("KSkillCore");
	KSkillCore.SayHello();

	UModuleExampleAsset* Asset = NewObject<UModuleExampleAsset>();
	Asset->Name = TEXT("FKSkillCore:lefeihu");
	Asset->Age = 100;
	UE_LOG(LogTemp, Log, TEXT("Name:%s, Age:%d"), *Asset->Name, Asset->Age);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

