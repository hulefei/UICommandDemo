// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntryActor.generated.h"

UCLASS()
class ACTIONNODEEXAMPLE_API AEntryActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntryActor();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABridgeActor> BridgeActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
