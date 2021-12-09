// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PREVIEWEXAMPLE_API STestPreview : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(STestPreview)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	private:
	TSharedPtr<class STestEditorViewport> TestEditorViewport;
	TSharedPtr<class STestTransportControls> TestTransportControls;
};
