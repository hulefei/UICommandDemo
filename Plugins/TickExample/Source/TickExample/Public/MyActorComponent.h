// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickTimelineComponent.h"
#include "Components/SceneComponent.h"
#include "MyActorComponent.generated.h"


class AMyBaseActor;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TICKEXAMPLE_API UMyActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyActorComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMyBaseActor> ActorBlueprint;
	UPROPERTY()
	AMyBaseActor* MyBaseActor = nullptr;
	UPROPERTY()
	FTickTimeline TickTimeline;

	virtual void Activate(bool bReset=false) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
