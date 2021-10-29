// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SCustomAssetKTimeline : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SCustomAssetKTimeline)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	// virtual FReply OnMouseWheel(SWidget& WidgetOwner, const FGeometry& MyGeometry,
	// 							const FPointerEvent& MouseEvent) override;
	
	void UpdateTrack() const;
void UpdateTrack_Move() const;

/* Our Action Container */
	TSharedPtr<class SCustomAssetKTimelineScrollBox> KTimelineScrollBox;
};
