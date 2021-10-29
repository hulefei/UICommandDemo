// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetTimeSliderController.h"


int32 FCustomAssetTimeSliderController::OnPaintTimeSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FSlateDrawElement::MakeBox(OutDrawElements,
							LayerId,
							AllottedGeometry.ToPaintGeometry(),
							TrackBrush, ESlateDrawEffect::None, FColor::Red);
	
	return LayerId;
}

int32 FCustomAssetTimeSliderController::OnPaintViewArea(const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled,
	const FPaintViewAreaArgs& Args) const
{
	return 0;
}

FReply FCustomAssetTimeSliderController::OnMouseButtonDown(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}

FReply FCustomAssetTimeSliderController::OnMouseButtonUp(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}

FReply FCustomAssetTimeSliderController::OnMouseMove(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}

FReply FCustomAssetTimeSliderController::OnMouseWheel(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}

FCursorReply FCustomAssetTimeSliderController::OnCursorQuery(TSharedRef<const SWidget> WidgetOwner,
	const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{
	return FCursorReply::Unhandled();
}

void FCustomAssetTimeSliderController::SetViewRange(double NewRangeMin, double NewRangeMax,
	EViewRangeInterpolation Interpolation)
{
}

void FCustomAssetTimeSliderController::SetClampRange(double NewRangeMin, double NewRangeMax)
{
}

void FCustomAssetTimeSliderController::SetPlayRange(FFrameNumber RangeStart, int32 RangeDuration)
{
}
