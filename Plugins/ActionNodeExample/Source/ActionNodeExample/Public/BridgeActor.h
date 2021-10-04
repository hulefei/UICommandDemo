// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BridgeActor.generated.h"

UCLASS()
class ACTIONNODEEXAMPLE_API ABridgeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABridgeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ~Core
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 DispatchEvent(FName EventName);
};
