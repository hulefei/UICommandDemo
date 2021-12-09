// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PREVIEWEXAMPLE_API STestTransportControls : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(STestTransportControls)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual FVector2D ComputeDesiredSize(float Scale) const override;
};
