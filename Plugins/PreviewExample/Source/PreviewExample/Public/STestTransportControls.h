// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ITransportControl.h"
#include "Widgets/SCompoundWidget.h"

class FTestEditorViewportClient;
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

public:
	TSharedPtr<FTestEditorViewportClient> TestEditorViewportClient;
	
private:
	TSharedPtr<class ITransportControl> TransportControl;
	
	
	
private:
	FReply OnClick_Forward_Step();
	FReply OnClick_Forward_End();
	FReply OnClick_Backward_Step();
	FReply OnClick_Backward_End();
	FReply OnClick_Forward();
	FReply OnClick_Backward();
	FReply OnClick_ToggleLoop();
	FReply OnClick_Record();

	bool IsLoopStatusOn() const;
	EPlaybackMode::Type GetPlaybackMode() const;
	bool IsRecording() const;

	
};
