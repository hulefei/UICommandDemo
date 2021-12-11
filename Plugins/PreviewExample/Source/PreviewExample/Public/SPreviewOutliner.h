// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PreviewTimelineTrack.h"
#include "Widgets/SCompoundWidget.h"

class SPreviewTrackArea;
/**
 * 
 */
class PREVIEWEXAMPLE_API SPreviewOutliner : public STreeView<TSharedRef<FPreviewTimelineTrack >>
{
public:
	SLATE_BEGIN_ARGS(SPreviewOutliner)
		{
		}

	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs, const TSharedRef<SPreviewTrackArea>& InTrackArea);
	
};
