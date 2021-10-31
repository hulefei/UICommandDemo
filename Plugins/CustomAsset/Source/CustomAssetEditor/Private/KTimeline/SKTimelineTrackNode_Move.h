// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SKTimelineTrackNode_Move : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SKTimelineTrackNode_Move)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
