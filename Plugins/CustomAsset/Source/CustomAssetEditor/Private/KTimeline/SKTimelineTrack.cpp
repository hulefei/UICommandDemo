// Fill out your copyright notice in the Description page of Project Settings.


#include "SKTimelineTrack.h"

#include "SlateOptMacros.h"
#include "SKTimelineTrackNode.h"
#include "SKTimelineTrackMoveNode.h"
#include "Styles/CustomAssetEditorStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKTimelineTrack::Construct(const FArguments& InArgs)
{
	this->ChildSlot
	    .HAlign(HAlign_Fill)
	    .Padding(0.0f)
	[

		SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Gray)
		.Content()
		[
			SAssignNew(NodeSlots, SOverlay)
			// + SOverlay::Slot()
			// [
			// 	SAssignNew(TrackNode, SKTimelineTrackNode)
			// ]
			// SAssignNew(TrackNode, SKTimelineTrackNode)
			// SAssignNew(TrackNode, SKTimelineTrackMoveNode)
		]
	];

	TrackBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.Timeline");
	FMargin Margin = FMargin(100, 0, 500, 0);
	//动态获取
	NodeSlots->AddSlot().Padding(TAttribute<FMargin>::Create(TAttribute<FMargin>::FGetter::CreateSP(this, &SKTimelineTrack::GetTrackPadding)))
	[
		SAssignNew(TrackNode, SKTimelineTrackNode)
	];
}

FVector2D SKTimelineTrack::ComputeDesiredSize(float Scale) const
{
	// Since it's Horizontal Fill, the X is ignored, we only care about the Y (Height).
	if (TrackNode.IsValid())
	{
		return TrackNode.Get()->ComputeDesiredSize(Scale);
	}

	return FVector2D(100.0f, 30.0f);
}

int32 SKTimelineTrack::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                               const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements,
                               int32 LayerId,
                               const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FSlateDrawElement::MakeBox(OutDrawElements,
	                           LayerId,
	                           AllottedGeometry.ToPaintGeometry(),
	                           TrackBrush, ESlateDrawEffect::None, FColor::Red);

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId + 1, InWidgetStyle,
	                                bParentEnabled);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION