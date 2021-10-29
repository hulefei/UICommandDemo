// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

enum EKSkillDragType
{
	MoveNone = 0,
	MoveCenter,
	MoveStart,
	MoveEnd,
	TotalTypes
};

class CUSTOMASSETEDITOR_API SKTimelineTrackNode : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SKTimelineTrackNode)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	// Rendering/Size overrides

	// Input catching
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//用于判断是否属于drag，在Move中可以直接使用
	virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//返回鼠标样式
	virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;

	// Rendering/Size overrides
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	//每帧draw
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect,
		FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	FLinearColor GetNodeColor() const;

private:
	FSlateFontInfo SlateFontInfo;
	const FSlateBrush* NodeBrush = nullptr;
	const FSlateBrush* HighlightNodeBrush = nullptr;
	const FSlateBrush* TextBackgroundBrush = nullptr;
	/* Our current Drag operation type. */
	EKSkillDragType DragType = EKSkillDragType::MoveNone;
	float MaxLength = 100.0f;
	float Duration = 50.f;
};
