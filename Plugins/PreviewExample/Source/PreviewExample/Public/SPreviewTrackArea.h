// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FPreviewTimeSliderController;
class SPreviewTrack;
/**
 * Structure representing a slot in the track area.
 */
class FPreviewTrackAreaSlot : public TSlotBase<FPreviewTrackAreaSlot>
{
public:

	/** Construction from a track lane */
	FPreviewTrackAreaSlot(const TSharedPtr<SPreviewTrack>& InSlotContent);

	/** Get the vertical position of this slot inside its parent. */
	float GetVerticalOffset() const;

	/** Horizontal/Vertical alignment for the slot. */
	EHorizontalAlignment HAlignment;
	EVerticalAlignment VAlignment;

	/** The track that we represent. */
	TWeakPtr<SPreviewTrack> TrackWidget;
};

class PREVIEWEXAMPLE_API SPreviewTrackArea : public SPanel
{
public:
	SLATE_BEGIN_ARGS(SPreviewTrackArea)
		{
		}

	SLATE_END_ARGS()

	SPreviewTrackArea()
		: Children(this)
	{}

	/** Construct this widget */
	void Construct(const FArguments& InArgs, const TSharedRef<FPreviewTimeSliderController>& InTimeSliderController);

	/** SWidget interface */
	virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;
	virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;
	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;
	virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual FChildren* GetChildren() override;

private:

	/** The track area's children. */
	TPanelChildren<FPreviewTrackAreaSlot> Children;
};
