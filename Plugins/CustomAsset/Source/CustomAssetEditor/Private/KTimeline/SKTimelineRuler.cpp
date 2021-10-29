// Fill out your copyright notice in the Description page of Project Settings.


#include "SKTimelineRuler.h"

#include "SlateOptMacros.h"

#include "Styles/CustomAssetEditorStyle.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "Rendering/SlateRenderer.h"
#include "Rendering/DrawElements.h"
#include "Rendering/SlateLayoutTransform.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKTimelineRuler::Construct(const FArguments& InArgs)
{
	SlateBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.Timeline");
	SlateFontInfo = FEditorStyle::GetFontStyle("PropertyWindow.NormalFont");
	SlateFontInfo.Size = 8;
	// ChildSlot
	// [
	// 	// Populate the widget
	//
	// ];
}

FVector2D SKTimelineRuler::ComputeDesiredSize(float Scale) const
{
	return FVector2D(100.0f, 26.0f);
}

int32 SKTimelineRuler::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                          const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                          const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D TimeRange(0.0f, 20.0f);
	const TSharedRef< FSlateFontMeasure > FontMeasureService = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();

	// if (KSkillEditorPtr.IsValid())
	// {
	// 	FSegmentContent SegmentContent = SKEditorPtr.Pin()->SKDataSkill->GetSegmentContent(SKEditorPtr.Pin()->GetCurrentSegment());
	// 	if (SegmentContent.SegmentId != 0)
	// 	{
	// 		TimeRange.Y = SegmentContent.Length;
	// 	}
	// }

	FNumberFormattingOptions FmtOptions;
	FmtOptions.SetMaximumFractionalDigits(2);
	FmtOptions.SetMinimumFractionalDigits(1);

	FText MinText = FText::AsNumber(TimeRange.X, &FmtOptions);
	FText MaxText = FText::AsNumber(TimeRange.Y, &FmtOptions);
	FVector2D MinSize = FontMeasureService->Measure(MinText, SlateFontInfo);
	FVector2D MaxSize = FontMeasureService->Measure(MaxText, SlateFontInfo);

	const FVector2D& WidgetSize = AllottedGeometry.GetLocalSize();

	// Our Padding is how much it takes to safely display our largest string.
	const float Padding = MaxSize.X * 0.5f;
	FVector2D TextOffset(0.0f, 0.0f);

	const float ScrollbarWidth = 12.0f;

	int32 CurrentLayer = LayerId;

	FSlateDrawElement::MakeBox(OutDrawElements,
		CurrentLayer++,
		AllottedGeometry.ToPaintGeometry(),
		SlateBrush);

	FSlateLayoutTransform Transform;

	// Right side (Max Time Label)
	TextOffset.X = WidgetSize.X - MaxSize.X * 0.5f - Padding - ScrollbarWidth;

	Transform = FSlateLayoutTransform(TextOffset);

	FSlateDrawElement::MakeText(OutDrawElements,
		CurrentLayer++,
		AllottedGeometry.ToPaintGeometry(Transform),
		MaxText,
		SlateFontInfo);

	// Lines
	float MajorLineSize = WidgetSize.Y * 0.5f;
	float MinorLineSize = WidgetSize.Y * 0.25f;

	TArray<FVector2D> Line; // Start/End points.
	Line.SetNum(2);

	float MajorFreq = 0.5f;
	float MinorFreq = 0.25f;

	// Major
	float StepTime = 0.0f;
	FText MajorLabel;

	Line[0].Y = WidgetSize.Y - 1.0f; // Bottom, minus a bit of padding.
	Line[1].Y = WidgetSize.Y - MajorLineSize;


	const float WidgetInteriorSize = WidgetSize.X - Padding * 2.0f - ScrollbarWidth; // We have padding on both ends.

	for (; StepTime < TimeRange.Y; StepTime += MajorFreq)
	{
		Line[0].X = Padding + WidgetInteriorSize * (StepTime / TimeRange.Y);
		Line[1].X = Line[0].X;

		FSlateDrawElement::MakeLines(OutDrawElements,
			CurrentLayer++,
			AllottedGeometry.ToPaintGeometry(),
			Line);

		{
			MajorLabel = FText::AsNumber(StepTime, &FmtOptions);

			TextOffset.X = Line[0].X - FontMeasureService->Measure(MajorLabel, SlateFontInfo).X * 0.5f;
			Transform = FSlateLayoutTransform(TextOffset);

			FSlateDrawElement::MakeText(OutDrawElements,
				CurrentLayer++,
				AllottedGeometry.ToPaintGeometry(Transform),
				MajorLabel,
				SlateFontInfo);
		}
	}

	// Minor
	for (StepTime = 0.0f; StepTime < TimeRange.Y; StepTime += MinorFreq)
	{
		Line[0].X = Padding + WidgetInteriorSize * (StepTime / TimeRange.Y);
		Line[1].X = Line[0].X;

		FSlateDrawElement::MakeLines(OutDrawElements,
			CurrentLayer++,
			AllottedGeometry.ToPaintGeometry(),
			Line);
	}

	// Far Right Line
	Line[0].X = WidgetSize.X - Padding - ScrollbarWidth;
	Line[1].X = Line[0].X;

	FSlateDrawElement::MakeLines(OutDrawElements,
		CurrentLayer++,
		AllottedGeometry.ToPaintGeometry(),
		Line);

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, CurrentLayer, InWidgetStyle, bParentEnabled);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
