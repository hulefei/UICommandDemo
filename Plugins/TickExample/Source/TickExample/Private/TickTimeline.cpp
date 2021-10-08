// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimeline.h"

// DEFINE_LOG_CATEGORY_STATIC(LogTickExample, Log, All);

void FTickTimeline::ConstructTimeline()
{
	bLooping = false;
	bPlaying = false;
	Position = 0;
	FrameNum = 0;
}

void FTickTimeline::Reset(const int32 InFrameNum, const bool InbLooping)
{
	ConstructTimeline();
	bLooping = InbLooping;
	FrameNum = InFrameNum;
}

void FTickTimeline::Play()
{
	bPlaying = true;
}

void FTickTimeline::PlayFromStart()
{
	Position = 0;
	bPlaying = true;
}

void FTickTimeline::Stop()
{
	bPlaying = false;
}

void FTickTimeline::TimelineTick(float DeltaTime)
{
	bool bIsFinished = false;

	if (bPlaying)
	{
		const int32 TimelineFrameNum = GetTimelineFrameNum();
		int32 NewPosition = Position + 1;
		if (NewPosition > TimelineFrameNum)
		{
			if (bLooping)
			{
				NewPosition = 0;
			}else
			{
				NewPosition = TimelineFrameNum;
				Stop();
				bIsFinished = true;
			}
		}
		SetPlaybackPosition(NewPosition, true);
	}

	if (bIsFinished)
	{
		//TODO: call finished
		TickTimelineFinishedFunc.ExecuteIfBound();
	}
}

void FTickTimeline::SetPlaybackPosition(int32 NewPosition, bool bFireEvents, bool bFireUpdate)
{
	Position = NewPosition;
	
	// Execute the delegate to say that all properties are updated
	if (bFireUpdate)
	{
		TimelinePostUpdateFunc.ExecuteIfBound();
	}
}

void FTickTimeline::SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc)
{
	TickTimelineFinishedFunc = NewTickTimelineFinishedFunc;
}

void FTickTimeline::SetTimelinePostUpdateFunc(FOnTickTimelineEvent NewTimelinePostUpdateFunc)
{
	TimelinePostUpdateFunc = NewTimelinePostUpdateFunc;
}
