// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TickTimeline.generated.h"

/** Signature of function to handle a timeline 'event' */
DECLARE_DYNAMIC_DELEGATE(FOnTickTimelineEvent);

/** Static version of delegate to handle a timeline 'event' */
DECLARE_DELEGATE(FOnTimelineEventStatic);

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
	uint32 Position;

	UPROPERTY()
	uint32 FrameNum;

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
	uint32 GetTimelineFrameNum() const { return FrameNum; }
	//返回Timeline 当前所在帧的位置
	uint32 GetTimelinePosition() const { return Position; }
	//设置timeline当前位置
	void SetPlaybackPosition(uint32 NewPosition, bool bFireEvents, bool bFireUpdate = true);

	UPROPERTY()
	/** Called whenever this timeline is finished. Is not called if 'stop' is used to terminate timeline early  */
	FOnTickTimelineEvent TickTimelineFinishedFunc;

	/** Set the delegate to call when timeline is finished */
	void SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc);

private:
	/** Called whenever this timeline is finished. Is not called if 'stop' is used to terminate timeline early  */
	FOnTimelineEventStatic TickTimelineFinishFuncStatic;
};
