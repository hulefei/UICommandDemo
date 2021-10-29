// Fill out your copyright notice in the Description page of Project Settings.


#include "SKTimelineTrackNode.h"

#include "SlateOptMacros.h"
#include "Styles/CustomAssetEditorStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKTimelineTrackNode::Construct(const FArguments& InArgs)
{
	SlateFontInfo = FEditorStyle::GetFontStyle("PropertyWindow.NormalFont");
	SlateFontInfo.Size = 12;
	NodeBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.Node");
	HighlightNodeBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.NodeHighlight");
	TextBackgroundBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.NodeText");

	DragType = MoveNone;
	MaxLength = 100.0f;

	
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FReply SKTimelineTrackNode::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const bool IsLMBDown = MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton);
	const bool IsRMBDown = MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton);
	if (IsLMBDown)
	{
		//TODO:判断类型
		DragType = MoveCenter;
		return FReply::Handled().DetectDrag(SharedThis(this), EKeys::LeftMouseButton);
	}

	return FReply::Unhandled();
}

FReply SKTimelineTrackNode::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	UE_LOG(LogTemp, Log, TEXT("SKSkillSimpleTimelineTrackNode::OnMouseButtonUp"));
	if (DragType != EKSkillDragType::MoveNone)
	{
		DragType = EKSkillDragType::MoveNone;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

FReply SKTimelineTrackNode::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!HasMouseCapture())
	{
		return FReply::Unhandled();
	}

	const FVector2D& ParentWidgetSize = MyGeometry.GetLocalSize();
	const FVector2D MousePos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
	float MouseTimePosition = MousePos.X / ParentWidgetSize.X * MaxLength;
	MouseTimePosition = FMath::Clamp(MouseTimePosition, 0.0f, MaxLength);
	Duration = MouseTimePosition;

	return FReply::Unhandled();
}

FReply SKTimelineTrackNode::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Handled().CaptureMouse(SharedThis(this));
}

FCursorReply SKTimelineTrackNode::OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{
	return FCursorReply::Cursor(EMouseCursor::GrabHand);
}

FVector2D SKTimelineTrackNode::ComputeDesiredSize(float Scale) const
{
	// Since it's Horizontal Fill, the X is ignored, we only care about the Y (Height).
	// if (TrackNode.IsValid())
	// {
	// 	return TrackNode.Get()->ComputeDesiredSize(Scale);
	// }
	return FVector2D(100.0f, 26.0f);
}

int32 SKTimelineTrackNode::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const TSharedRef<FSlateFontMeasure> FontMeasureService = FSlateApplication::Get().GetRenderer()->
		GetFontMeasureService();
	const FVector2D& ParentWidgetSize = AllottedGeometry.GetLocalSize();
	const FVector2D DependencyIconSize(12.0f, 12.0f);
	const FVector2D TextBackgroundPadding(2.0f, 0.0f);

	float SegmentStartTime = 0.0f;
	// MaxLength = FMath::Clamp(MaxLength, 0.1f, 10.00f);

	float ActionSizeRatio = Duration == 0 ? MaxLength * 0.05f : Duration / MaxLength;
	ActionSizeRatio = FMath::Clamp(ActionSizeRatio, 0.05f, 1.0f);
	const float Size = ParentWidgetSize.X * ActionSizeRatio;

	int32 CurrentLayer = LayerId;
	const FVector2D NodeSize(Size, ParentWidgetSize.Y);
	// const FVector2D NodeSize(15, 15);
	const FVector2D NodeTranslation(0, 0.0f);
	const FSlateLayoutTransform NodeOffset(NodeTranslation);

	// Node
	FSlateDrawElement::MakeBox(OutDrawElements,
							CurrentLayer++,
							AllottedGeometry.ToPaintGeometry(NodeSize, NodeOffset),
							NodeBrush,
							ESlateDrawEffect::None,
							GetNodeColor());
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle,
									bParentEnabled);
}

FLinearColor SKTimelineTrackNode::GetNodeColor() const
{
	return FLinearColor::Yellow;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
