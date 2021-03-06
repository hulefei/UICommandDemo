// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "TickEntryActor.generated.h"

UCLASS()
class TICKEXAMPLE_API ATickEntryActor : public AActor
{
	GENERATED_BODY()

	public:
	// Sets default values for this actor's properties
	ATickEntryActor();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnTickTimelineUpdateEventHandle(int32 Position);
	
	UFUNCTION(BlueprintCallable)
	virtual void OnTickTimelineFinishedEventHandle();

	UFUNCTION(BlueprintCallable)
	virtual void OnTickTimelineEventHandle();

	UFUNCTION(BlueprintCallable)
	void OnTickTimelineKeyframeEventHandle(FName Name);
	

	UPROPERTY()
	class UMyActorComponent* MyActorComponent;
};
