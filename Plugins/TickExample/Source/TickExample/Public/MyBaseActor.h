// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActorComponent.h"
#include "GameFramework/Actor.h"
#include "MyBaseActor.generated.h"

UCLASS()
class TICKEXAMPLE_API AMyBaseActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	explicit AMyBaseActor(const FObjectInitializer& ObjectInitializer);
	UPROPERTY()
	UMyActorComponent* MyActorComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
