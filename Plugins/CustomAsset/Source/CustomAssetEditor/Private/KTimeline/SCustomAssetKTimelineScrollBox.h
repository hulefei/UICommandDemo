// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Layout/SScrollBox.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SCustomAssetKTimelineScrollBox : public SScrollBox
{
	public:
	SLATE_BEGIN_ARGS(SCustomAssetKTimelineScrollBox)
	{
	}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override;

	// TSharedRef<SWidget> GenerateActionContextMenu();
};
