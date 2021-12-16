#include "PreviewTimeSliderController.h"

FPreviewTimeSliderController::FPreviewTimeSliderController(const FTimeSliderArgs& InArgs,
	TWeakPtr<SPreviewTimeline> InWeakTimeline,
	TSharedPtr<INumericTypeInterface<double>> InSecondaryNumericTypeInterface)
{
	ScrubFillBrush              = FEditorStyle::GetBrush( TEXT( "Sequencer.Timeline.ScrubFill" ) );
	ScrubHandleUpBrush          = FEditorStyle::GetBrush( TEXT( "Sequencer.Timeline.VanillaScrubHandleUp" ) ); 
	ScrubHandleDownBrush        = FEditorStyle::GetBrush( TEXT( "Sequencer.Timeline.VanillaScrubHandleDown" ) );
	EditableTimeBrush            = FEditorStyle::GetBrush( TEXT( "AnimTimeline.SectionMarker" ) );
}

int32 FPreviewTimeSliderController::OnPaintTimeSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//draw Slider
	const bool bEnabled = bParentEnabled;
	const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	const FSlateBrush* Brush = (bMirrorLabels ? ScrubHandleUpBrush : ScrubHandleDownBrush);

	// Draw the scrub handle
	const float      HandleStart        = 0;//RangeToScreen.InputToLocalX(TimeSliderArgs.ScrubPosition.Get().AsDecimal() / GetTickResolution().AsDecimal()) - 7.0f;
	const float      HandleEnd          = HandleStart + 13.0f;
	
	const int32 ArrowLayer = LayerId + 2;
	FPaintGeometry MyGeometry =	AllottedGeometry.ToPaintGeometry( FVector2D( HandleStart, 0 ), FVector2D( HandleEnd - HandleStart, AllottedGeometry.Size.Y ) );
	FLinearColor ScrubColor = InWidgetStyle.GetColorAndOpacityTint();
	{
		ScrubColor.A = ScrubColor.A * 0.75f;
		ScrubColor.B *= 0.1f;
		ScrubColor.G *= 0.2f;
	}
	
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		ArrowLayer,
		MyGeometry,
		Brush,
		DrawEffects,
		ScrubColor
	);
	
	return 0;
}

int32 FPreviewTimeSliderController::OnPaintViewArea(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args) const
{
	return 0;
}

FReply FPreviewTimeSliderController::OnMouseButtonDown(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Handled();
}

FReply FPreviewTimeSliderController::OnMouseButtonUp(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Handled();
}

FReply FPreviewTimeSliderController::OnMouseMove(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Handled();
}

FReply FPreviewTimeSliderController::OnMouseWheel(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Handled();
}

FCursorReply FPreviewTimeSliderController::OnCursorQuery(TSharedRef<const SWidget> WidgetOwner,
	const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{
	return FCursorReply::Unhandled();
}

void FPreviewTimeSliderController::SetViewRange(double NewRangeMin, double NewRangeMax,
	EViewRangeInterpolation Interpolation)
{
	ITimeSliderController::SetViewRange(NewRangeMin, NewRangeMax, Interpolation);
}

void FPreviewTimeSliderController::SetClampRange(double NewRangeMin, double NewRangeMax)
{
	ITimeSliderController::SetClampRange(NewRangeMin, NewRangeMax);
}

void FPreviewTimeSliderController::SetPlayRange(FFrameNumber RangeStart, int32 RangeDuration)
{
	ITimeSliderController::SetPlayRange(RangeStart, RangeDuration);
}
