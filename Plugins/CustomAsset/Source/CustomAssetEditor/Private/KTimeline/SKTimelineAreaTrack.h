// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SKTimelineSection.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SKTimelineAreaTrack : public SPanel
{
public:
SLATE_BEGIN_ARGS(SKTimelineAreaTrack)
		{
		}

	/** The view range of the section area */
	SLATE_ATTRIBUTE( TRange<double>, ViewRange )
	SLATE_END_ARGS()

	SKTimelineAreaTrack() : Children(this) {}
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	/** The current view range */
	TAttribute< TRange<double> > ViewRange;
	/** All the widgets in the panel */
	TSlotlessChildren<SKTimelineSection> Children;
};
