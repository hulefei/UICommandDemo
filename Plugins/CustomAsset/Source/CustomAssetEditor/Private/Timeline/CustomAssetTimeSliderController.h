// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/CursorReply.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "Editor/SequencerWidgets/Public/ITimeSlider.h"
/**
 * 
 */
class CUSTOMASSETEDITOR_API FCustomAssetTimeSliderController : public ITimeSliderController,
                                                               public TSharedFromThis<FCustomAssetTimeSliderController>
{
	/** ITimeSliderController Interface */
	virtual int32 OnPaintTimeSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry,
	                                const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
	                                int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                                bool bParentEnabled) const override;
	virtual int32 OnPaintViewArea(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	                              FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled,
	                              const FPaintViewAreaArgs& Args) const override;
	virtual FReply OnMouseButtonDown(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	                                 const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	                               const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	                           const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseWheel(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	                            const FPointerEvent& MouseEvent) override;
	virtual FCursorReply OnCursorQuery(TSharedRef<const SWidget> WidgetOwner, const FGeometry& MyGeometry,
	                                   const FPointerEvent& CursorEvent) const override;

	// int32 DrawEditableTimes(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen) const;

	virtual void SetViewRange(double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation) override;
	virtual void SetClampRange(double NewRangeMin, double NewRangeMax) override;
	virtual void SetPlayRange(FFrameNumber RangeStart, int32 RangeDuration) override;
	virtual FFrameRate GetDisplayRate() const override { return TimeSliderArgs.DisplayRate.Get(); }
	virtual FFrameRate GetTickResolution() const override { return TimeSliderArgs.TickResolution.Get(); }
	virtual FAnimatedRange GetViewRange() const override { return TimeSliderArgs.ViewRange.Get(); }
	virtual FAnimatedRange GetClampRange() const override { return TimeSliderArgs.ClampRange.Get(); }

	virtual TRange<FFrameNumber> GetPlayRange() const override
	{
		return TimeSliderArgs.PlaybackRange.Get(TRange<FFrameNumber>());
	}

	virtual FFrameTime GetScrubPosition() const override { return TimeSliderArgs.ScrubPosition.Get(); }

	virtual void SetScrubPosition(FFrameTime InTime) override
	{
		TimeSliderArgs.OnScrubPositionChanged.ExecuteIfBound(InTime, false);
	}

	/** End ITimeSliderController Interface */

private:
	FTimeSliderArgs TimeSliderArgs;
};
