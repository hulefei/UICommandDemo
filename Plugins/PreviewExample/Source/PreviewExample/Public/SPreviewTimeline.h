// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FPreviewTimeSliderController;
class ITimeSlider;
struct FAnimatedRange;
/**
 * 
 */
class PREVIEWEXAMPLE_API SPreviewTimeline : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPreviewTimeline)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex);

private:
	/** The fill coefficients of each column in the grid. */
	float ColumnFillCoefficients[2];
	/** The search box for filtering tracks. */
	TSharedPtr<SSearchBox> SearchBox;

	/** Called when the user has begun dragging the selection selection range */
	FSimpleDelegate OnSelectionRangeBeginDrag;

	/** Called when the user has finished dragging the selection selection range */
	FSimpleDelegate OnSelectionRangeEndDrag;

	/** Called when any widget contained within the anim timeline has received focus */
	FSimpleDelegate OnReceivedFocus;

	/** Numeric Type interface for converting between frame numbers and display formats. */
	TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;

	/** Secondary numeric Type interface for converting between frame numbers and display formats. */
	TSharedPtr<INumericTypeInterface<double>> SecondaryNumericTypeInterface;

	/** The view range */
	// TAttribute<FAnimatedRange> ViewRange;

	/** Filter text used to search the tree */
	FText FilterText;

	/** The top time slider widget */
	TSharedPtr<ITimeSlider> TopTimeSlider;

	/** The time slider controller */
	TSharedPtr<FPreviewTimeSliderController> TimeSliderController;
private:
	/**
	 * @return The fill percentage of the animation outliner
	 */
	float GetColumnFillCoefficient(int32 ColumnIndex) const
	{
		return ColumnFillCoefficients[ColumnIndex];
	}
};
