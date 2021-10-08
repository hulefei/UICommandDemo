// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionData.h"
#include "GameFramework/Actor.h"
#include "EntryActor.generated.h"

UCLASS()
class ACTIONNODEEXAMPLE_API AEntryActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	FActionData EntryActionData;

	UPROPERTY()
	TMap<int32, FActionData> ActionDataMap;
};
