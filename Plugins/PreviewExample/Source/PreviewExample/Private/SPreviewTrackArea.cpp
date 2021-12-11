// Fill out your copyright notice in the Description page of Project Settings.


#include "SPreviewTrackArea.h"

#include "SlateOptMacros.h"
#include "SPreviewTrack.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FPreviewTrackAreaSlot::FPreviewTrackAreaSlot(const TSharedPtr<SPreviewTrack>& InSlotContent)
{
	TrackWidget = InSlotContent;
	
	HAlignment = HAlign_Fill;
	VAlignment = VAlign_Top;

	// AttachWidget(
	// 	SNew(SWeakWidget)
	// 	.Clipping(EWidgetClipping::ClipToBounds)
	// 	.PossiblyNullContent(InSlotContent)
	// );
}

float FPreviewTrackAreaSlot::GetVerticalOffset() const
{
	TSharedPtr<SPreviewTrack> PinnedTrackWidget = TrackWidget.Pin();
	// return PinnedTrackWidget.IsValid() ? PinnedTrackWidget->GetPhysicalPosition() : 0.f;
	return 0.f;
}

void SPreviewTrackArea::Construct(const FArguments& InArgs,
                                  const TSharedRef<FPreviewTimeSliderController>& InTimeSliderController)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FReply SPreviewTrackArea::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return SPanel::OnMouseButtonDown(MyGeometry, MouseEvent);
}

FReply SPreviewTrackArea::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return SPanel::OnMouseButtonUp(MyGeometry, MouseEvent);
}

FReply SPreviewTrackArea::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return SPanel::OnMouseMove(MyGeometry, MouseEvent);
}

void SPreviewTrackArea::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	SPanel::OnMouseLeave(MouseEvent);
}

FReply SPreviewTrackArea::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return SPanel::OnMouseWheel(MyGeometry, MouseEvent);
}

int32 SPreviewTrackArea::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	return SPanel::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                       bParentEnabled);
}

FCursorReply SPreviewTrackArea::OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{
	return SPanel::OnCursorQuery(MyGeometry, CursorEvent);
}

void SPreviewTrackArea::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SPanel::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

void SPreviewTrackArea::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	for (int32 ChildIndex = 0; ChildIndex < Children.Num(); ++ChildIndex)
	{
		const FPreviewTrackAreaSlot& CurChild = Children[ChildIndex];

		const EVisibility ChildVisibility = CurChild.GetWidget()->GetVisibility();
		if (!ArrangedChildren.Accepts(ChildVisibility))
		{
			continue;
		}

		const FMargin Padding(0, CurChild.GetVerticalOffset(), 0, 0);

		AlignmentArrangeResult XResult = AlignChild<Orient_Horizontal>(AllottedGeometry.GetLocalSize().X, CurChild, Padding, 1.0f, false);
		AlignmentArrangeResult YResult = AlignChild<Orient_Vertical>(AllottedGeometry.GetLocalSize().Y, CurChild, Padding, 1.0f, false);

		ArrangedChildren.AddWidget(ChildVisibility,
			AllottedGeometry.MakeChild(
				CurChild.GetWidget(),
				FVector2D(XResult.Offset, YResult.Offset),
				FVector2D(XResult.Size, YResult.Size)
			)
		);
	}
}

FVector2D SPreviewTrackArea::ComputeDesiredSize(float) const
{
	FVector2D MaxSize(0.0f, 0.0f);
	for (int32 ChildIndex = 0; ChildIndex < Children.Num(); ++ChildIndex)
	{
		const FPreviewTrackAreaSlot& CurChild = Children[ChildIndex];

		const EVisibility ChildVisibilty = CurChild.GetWidget()->GetVisibility();
		if (ChildVisibilty != EVisibility::Collapsed)
		{
			FVector2D ChildDesiredSize = CurChild.GetWidget()->GetDesiredSize();
			MaxSize.X = FMath::Max(MaxSize.X, ChildDesiredSize.X);
			MaxSize.Y = FMath::Max(MaxSize.Y, ChildDesiredSize.Y);
		}
	}

	return MaxSize;
}

FChildren* SPreviewTrackArea::GetChildren()
{
	return &Children;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
