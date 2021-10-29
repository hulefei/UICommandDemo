// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SKTimelineFrameRuler : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SKTimelineFrameRuler)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	// Rendering/Size overrides
	virtual FVector2D ComputeDesiredSize(float Scale) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect,
	                      FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                      bool bParentEnabled) const override;

private:
	/* Brush for our widget. */
	const FSlateBrush* SlateBrush = nullptr;

	/* Font information for our widget. */
	FSlateFontInfo SlateFontInfo;
};
