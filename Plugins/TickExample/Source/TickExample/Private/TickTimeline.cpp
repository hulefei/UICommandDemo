// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTimeline.h"

// DEFINE_LOG_CATEGORY_STATIC(LogTickExample, Log, All);

void FTickTimeline::ConstructTimeline()
{
	Events.Empty();
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
			}
			else
			{
				NewPosition = TimelineFrameNum;
				Stop();
				bIsFinished = true;
			}
		} else
		{
			//只有小于等于最大帧数时才执行
			SetPlaybackPosition(NewPosition, true);		
		}
	}

	if (bIsFinished)
	{
		TickTimelineFinishFunc.ExecuteIfBound();
		TickTimelineFinishFuncStatic.ExecuteIfBound();
	}
}

void FTickTimeline::SetPlaybackPosition(int32 NewPosition, bool bFireEvents, bool bFireUpdate)
{
	Position = NewPosition;

	// See which events fall into traversed region.
	for (int32 i = 0; i < Events.Num(); i++)
	{
		const float EventKeyframe = Events[i].Keyframe;

		// Need to be slightly careful here and make behavior for firing events symmetric when playing forwards of backwards.
		bool bFireThisEvent = false;
		if (EventKeyframe == Position)
		{
			bFireThisEvent = true;
		}

		if (bFireThisEvent)
		{
			Events[i].EventFunc.ExecuteIfBound(Events[i].Name);
		}
	}
	
	// Execute the delegate to say that all properties are updated
	if (bFireUpdate)
	{
		TickTimelinePostUpdateFunc.ExecuteIfBound(NewPosition);
		TickTimelinePostUpdateFuncStatic.ExecuteIfBound(NewPosition);
	}
}

void FTickTimeline::SetTickTimelineFinishedFunc(FOnTickTimelineEvent NewTickTimelineFinishedFunc)
{
	TickTimelineFinishFunc = NewTickTimelineFinishedFunc;
}

void FTickTimeline::SetTimelinePostUpdateFunc(FOnTickTimelineUpdateEvent NewTimelinePostUpdateFunc)
{
	TickTimelinePostUpdateFunc = NewTimelinePostUpdateFunc;
}

void FTickTimeline::SetTickTimelineFinishedFunc(FOnTickTimelineEventStatic NewTickTimelineFinishedFunc)
{
	TickTimelineFinishFuncStatic = NewTickTimelineFinishedFunc;
}

void FTickTimeline::SetTimelinePostUpdateFunc(FOnTickTimelineUpdateEventStatic NewTimelinePostUpdateFunc)
{
	TickTimelinePostUpdateFuncStatic = NewTimelinePostUpdateFunc;
}

void FTickTimeline::AddEvent(FName EventName, int32 Keyframe, FOnTickTimelineKeyframeEvent Event)
{
	FTickTimelineEventEntry NewEntry;
	NewEntry.Name = EventName;
	NewEntry.Keyframe = Keyframe;
	NewEntry.EventFunc = Event;

	Events.Add(NewEntry);
}
