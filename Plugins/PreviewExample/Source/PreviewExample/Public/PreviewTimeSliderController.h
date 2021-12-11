#pragma once
#include "CoreMinimal.h"
#include "Input/CursorReply.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "ITimeSlider.h"
#include "SPreviewTimeline.h"

class FPreviewTimeSliderController : public ITimeSliderController
{
public:
	FPreviewTimeSliderController( const FTimeSliderArgs& InArgs, TWeakPtr<SPreviewTimeline> InWeakTimeline, TSharedPtr<INumericTypeInterface<double>> InSecondaryNumericTypeInterface );

	/** ITimeSliderController Interface */
	virtual int32 OnPaintTimeSlider( bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;
	virtual int32 OnPaintViewArea( const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args ) const override;
	virtual FReply OnMouseButtonDown( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FReply OnMouseButtonUp( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FReply OnMouseMove( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FReply OnMouseWheel( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FCursorReply OnCursorQuery( TSharedRef<const SWidget> WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;
	virtual void SetViewRange( double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation ) override;
	virtual void SetClampRange( double NewRangeMin, double NewRangeMax ) override;
	virtual void SetPlayRange( FFrameNumber RangeStart, int32 RangeDuration ) override;
	virtual FFrameRate GetDisplayRate() const override { return TimeSliderArgs.DisplayRate.Get(); }
	virtual FFrameRate GetTickResolution() const override { return TimeSliderArgs.TickResolution.Get(); }
	virtual FAnimatedRange GetViewRange() const override { return TimeSliderArgs.ViewRange.Get(); }
	virtual FAnimatedRange GetClampRange() const override { return TimeSliderArgs.ClampRange.Get(); }
	virtual TRange<FFrameNumber> GetPlayRange() const override { return TimeSliderArgs.PlaybackRange.Get(TRange<FFrameNumber>()); }
	virtual FFrameTime GetScrubPosition() const { return TimeSliderArgs.ScrubPosition.Get(); }
	virtual void SetScrubPosition(FFrameTime InTime) { TimeSliderArgs.OnScrubPositionChanged.ExecuteIfBound(InTime, false); }
	/** End ITimeSliderController Interface */

private:

	/** Pointer back to the timeline */
	TWeakPtr<SPreviewTimeline> WeakTimeline;

	FTimeSliderArgs TimeSliderArgs;

	/** Brush for drawing the fill area on the scrubber */
	const FSlateBrush* ScrubFillBrush;

	/** Brush for drawing an upwards facing scrub handles */
	const FSlateBrush* ScrubHandleUpBrush;
	
	/** Brush for drawing a downwards facing scrub handle */
	const FSlateBrush* ScrubHandleDownBrush;

	/** Brush for drawing an editable time */
	const FSlateBrush* EditableTimeBrush;
	
	/** Total mouse delta during dragging **/
	float DistanceDragged;
	
	/** If we are dragging a scrubber or dragging to set the time range */
	enum DragType
	{
		DRAG_SCRUBBING_TIME,
		DRAG_SETTING_RANGE,
		DRAG_PLAYBACK_START,
		DRAG_PLAYBACK_END,
		DRAG_SELECTION_START,
		DRAG_SELECTION_END,
		DRAG_TIME,
		DRAG_NONE
	};
	
	DragType MouseDragType;
	
	/** If we are currently panning the panel */
	bool bPanning;

	/** Index of the current dragged time */
	int32 DraggedTimeIndex;

	/** Mouse down position range */
	FVector2D MouseDownPosition[2];

	/** Geometry on mouse down */
	FGeometry MouseDownGeometry;

	/** Range stack */
	TArray<TRange<double>> ViewRangeStack;

	/** Secondary numeric type interface for displaying 'other' numeric types */
	TSharedPtr<INumericTypeInterface<double>> SecondaryNumericTypeInterface;
};
