// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TickTimeline.generated.h"


/** Signature of function to handle a timeline 'event' */
DECLARE_DYNAMIC_DELEGATE(FOnTickTimelineEvent);
/** Signature of function to handle timeline 'update event' */
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTickTimelineUpdateEvent, int32, Output );
/** Signature of function to handle timeline 'keyframe event' */
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTickTimelineKeyframeEvent, FName, Output );

/** Static version of delegate to handle a timeline 'event' */
DECLARE_DELEGATE(FOnTickTimelineEventStatic);
/** Static version of delegate to handle a timeline 'update event' */
DECLARE_DELEGATE_OneParam(FOnTickTimelineUpdateEventStatic, int32);
/** Static version of delegate to handle a timeline 'keyframe event' */
DECLARE_DELEGATE_OneParam(FOnTickTimelineKeyframeEventStatic, FName);

/** Struct that contains one entry for an 'event' during the timeline */
USTRUCT()
struct FTickTimelineEventEntry
{
	GENERATED_USTRUCT_BODY()

	/** Name at which event should fire */
	UPROPERTY()
	FName Name;
	
	/** keyframe at which event should fire */
	UPROPERTY()
	int32 Keyframe;

	/** Function to execute when Time is reached */
	UPROPERTY()
	FOnTickTimelineKeyframeEvent EventFunc;


	FTickTimelineEventEntry() : Keyframe(0)
	{
	}

};

/** Struct that contains data */
USTRUCT()
struct FTickTimeline
{
	GENERATED_USTRUCT_BODY()

private:
	/** Whether timeline should loop when it reaches the end, or stop */
	UPROPERTY()
	uint8 bLooping:1;

	UPROPERTY()
	uint8 bPlaying:1;

	UPROPERTY()
	int32 Position;

	UPROPERTY()
	int32 FrameNum;

	/** Array of events that are fired at various times during the timeline */
	UPROPERTY(NotReplicated)
	TArray<FTickTimelineEventEntry> Events;

public:
	FTickTimeline()
	{
		ConstructTimeline();
	}

	void ConstructTimeline();
	
	void Reset(int32 InFrameNum, bool InbLooping = false);

	void Play();
	void PlayFromStart();
	void Stop();
	// 根据外部Tick更新Timeline
	void TimelineTick(float DeltaTime);
	
	//返回Timeline 总帧数
	int32 GetTimelineFrameNum() const { return FrameNum; }
	//返回Timeline 当前所在帧的位置
	
	int32 GetTimelinePosition() const { return Position; }
	//设置timeline当前位置
	void SetPlaybackPosition(int32 NewPosition, bool bFireEvents, bool bFireUpdate = true);

	/** Set the delegate to call when timeline is finished */
	void SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc);

	/** Set the delegate to call after each timeline tick */
	void SetTimelinePostUpdateFunc(FOnTickTimelineUpdateEvent NewTimelinePostUpdateFunc);

	/** Set the delegate to call when timeline is finished */
	void SetTickTimelineFinishedFunc(FOnTickTimelineEventStatic NewTickTimelineFinishedFunc);

	/** Set the delegate to call after each timeline tick */
	void SetTimelinePostUpdateFunc(FOnTickTimelineUpdateEventStatic NewTimelinePostUpdateFunc);

	void AddEvent(FName EventName, int32 Keyframe, FOnTickTimelineKeyframeEvent Event);

private:
	/** Called whenever this timeline is playing and updates - done after all delegates are executed and variables updated  */
	UPROPERTY(NotReplicated)
	FOnTickTimelineUpdateEvent TickTimelinePostUpdateFunc;
	
	UPROPERTY(NotReplicated)
	/** Called whenever this timeline is finished. Is not called if 'stop' is used to terminate timeline early  */
	FOnTickTimelineEvent TickTimelineFinishFunc;
	
	/** Called whenever this timeline is finished. Is not called if 'stop' is used to terminate timeline early  */
	FOnTickTimelineEventStatic TickTimelineFinishFuncStatic;

	/** Called whenever this timeline is playing and updates - done after all delegates are executed and variables updated  */
	FOnTickTimelineUpdateEventStatic TickTimelinePostUpdateFuncStatic;

	/** Called whenever this timeline keyframe is fired.*/
	FOnTickTimelineKeyframeEvent TickTimelineKeyframeFunc;
	
	/** Called whenever this timeline keyframe is fired.*/
	FOnTickTimelineKeyframeEventStatic TickTimelineKeyframeFuncStatic;
	
};
