// Fill out your copyright notice in the Description page of Project Settings.


#include "SKTimelineTrackNode.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKTimelineTrackNode::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FVector2D SKTimelineTrackNode::ComputeDesiredSize(float Scale) const
{
	// Since it's Horizontal Fill, the X is ignored, we only care about the Y (Height).
	// if (TrackNode.IsValid())
	// {
	// 	return TrackNode.Get()->ComputeDesiredSize(Scale);
	// }
	return FVector2D(100.0f, 30.0f);
}

int32 SKTimelineTrackNode::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	return 0;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
