// Fill out your copyright notice in the Description page of Project Settings.


#include "SKTimelineTrackMoveNode.h"

#include "SlateOptMacros.h"
#include "Styles/CustomAssetEditorStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKTimelineTrackMoveNode::Construct(const FArguments& InArgs)
{
	SlateFontInfo = FEditorStyle::GetFontStyle("PropertyWindow.NormalFont");
	SlateFontInfo.Size = 12;
	NodeBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.Node");
	HighlightNodeBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.NodeHighlight");
	TextBackgroundBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.NodeText");

	DragType = TMoveNone;
	MaxLength = 100.0f;
	
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FReply SKTimelineTrackMoveNode::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const bool IsLMBDown = MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton);
	const bool IsRMBDown = MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton);
	if (IsLMBDown)
	{
		//TODO:判断类型
		DragType = TMoveCenter;
		return FReply::Handled().DetectDrag(SharedThis(this), EKeys::LeftMouseButton);
	}

	return FReply::Unhandled();
}

FReply SKTimelineTrackMoveNode::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (DragType != EKMoveType::TMoveNone)
	{
		DragType = EKMoveType::TMoveNone;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

FReply SKTimelineTrackMoveNode::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!HasMouseCapture())
	{
		return FReply::Unhandled();
	}

	const FVector2D& ParentWidgetSize = MyGeometry.GetLocalSize();
	const FVector2D MousePos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
	// float MouseTimePosition = MousePos.X / ParentWidgetSize.X * MaxLength;
	// MouseTimePosition = FMath::Clamp(MouseTimePosition, 0.0f, MaxLength);
	Duration = MousePos.X;

	return FReply::Unhandled();
}

FReply SKTimelineTrackMoveNode::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Handled().CaptureMouse(SharedThis(this));
}

FCursorReply SKTimelineTrackMoveNode::OnCursorQuery(const FGeometry& MyGeometry,
	const FPointerEvent& CursorEvent) const
{
	return FCursorReply::Cursor(EMouseCursor::GrabHand);
}

FVector2D SKTimelineTrackMoveNode::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(100.0f, 26.0f);
}

int32 SKTimelineTrackMoveNode::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 CurrentLayer = LayerId;
	const TSharedRef<FSlateFontMeasure> FontMeasureService = FSlateApplication::Get().GetRenderer()->
		GetFontMeasureService();
	const FVector2D& ParentWidgetSize = AllottedGeometry.GetLocalSize();

	//Code...

	const FVector2D NodeSize(ParentWidgetSize.Y, ParentWidgetSize.Y);
	// const FVector2D NodeSize(15, 15);
	const FVector2D NodeTranslation(Duration - 13, 0.0f);
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

FLinearColor SKTimelineTrackMoveNode::GetNodeColor() const
{
	return FLinearColor::Yellow;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
