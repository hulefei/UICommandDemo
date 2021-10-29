// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SCustomAssetTimeline : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SCustomAssetTimeline)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	/** The fill coefficients of each column in the grid. */
	float ColumnFillCoefficients[2];

private:
	/**
	* @return The fill percentage of the animation outliner
	*/
	float GetColumnFillCoefficient(int32 ColumnIndex) const
	{
		return ColumnFillCoefficients[ColumnIndex];
	}
};
