#include "PreviewTimeSliderController.h"

FPreviewTimeSliderController::FPreviewTimeSliderController(const FTimeSliderArgs& InArgs,
	TWeakPtr<SPreviewTimeline> InWeakTimeline,
	TSharedPtr<INumericTypeInterface<double>> InSecondaryNumericTypeInterface)
{
	
}

int32 FPreviewTimeSliderController::OnPaintTimeSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
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
