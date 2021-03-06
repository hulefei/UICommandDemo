// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickTimeline.h"

#include "MyActorComponent.generated.h"

class AMyBaseActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TICKEXAMPLE_API UMyActorComponent : public UActorComponent
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
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	//设置TickTimeline
	UFUNCTION(BlueprintCallable)
	void ResetTimeline(const int32 InFrameNum, const bool InbLooping = false);
	UFUNCTION(BlueprintCallable)
	void Play();
	UFUNCTION(BlueprintCallable)
	void PlayFromStart();
	UFUNCTION(BlueprintCallable)
	void Stop();


	/** Add a callback event to the timeline */
	void AddEvent(FName Name, int32 Keyframe, FOnTickTimelineKeyframeEvent EventFunc);
	
	/** Set the delegate to call when timeline is finished */
	void SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc);

	/** Set the delegate to call after each timeline tick */
	void SetTickTimelinePostUpdateFunc(FOnTickTimelineUpdateEvent NewTimelinePostUpdateFunc);

	/** Set the delegate to call when timeline is finished */
	void SetTickTimelineFinishedFunc(FOnTickTimelineEventStatic NewTickTimelineFinishedFunc);

	/** Set the delegate to call after each timeline tick */
	void SetTickTimelinePostUpdateFunc(FOnTickTimelineUpdateEventStatic NewTimelinePostUpdateFunc);
};
