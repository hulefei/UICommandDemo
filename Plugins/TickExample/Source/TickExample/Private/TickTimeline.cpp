// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimeline.h"


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
	bPlaying = true;
}

void FTickTimeline::Stop()
{
	bPlaying = false;
}

void FTickTimeline::TimelineTick(float DeltaTime)
{
	bool bIsFinished = false;

	UE_LOG(LogTemp, Log, TEXT("FTickTimeline::TimelineTick"));
	
	if (bPlaying)
	{
		const uint32 TimelineFrameNum = GetTimelineFrameNum();
		float NewPosition = Position + 1;
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

void FTickTimeline::SetPlaybackPosition(uint32 NewPosition, bool bFireEvents, bool bFireUpdate)
{
	Position = NewPosition;
}

void FTickTimeline::SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc)
{
	UE_LOG(LogTemp, Log, TEXT("FTickTimeline::SetTickTimelineFinishedFunc"));
	TickTimelineFinishedFunc = NewTickTimelineFinishedFunc;
}
