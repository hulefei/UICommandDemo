// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TickTimeline.h"

#include "TickTimelineComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TICKEXAMPLE_API UTickTimelineComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTickTimelineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//~ Begin ActorComponent Interface.
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	virtual bool IsReadyForOwnerToAutoDestroy() const override;
	//~ End ActorComponent Interface.

private:
	/** The actual timeline structure */
	UPROPERTY()
	FTickTimeline TheTimeline;
};
