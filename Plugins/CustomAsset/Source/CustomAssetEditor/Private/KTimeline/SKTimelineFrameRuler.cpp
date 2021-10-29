// Fill out your copyright notice in the Description page of Project Settings.


#include "SKTimelineFrameRuler.h"

#include "SlateOptMacros.h"

#include "Styles/CustomAssetEditorStyle.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "Rendering/SlateRenderer.h"
#include "Rendering/DrawElements.h"
#include "Rendering/SlateLayoutTransform.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SKTimelineFrameRuler::Construct(const FArguments& InArgs)
{
	SlateBrush = FCustomAssetEditorStyle::GetBrush("CustomAssetEditor.Timeline");
	SlateFontInfo = FEditorStyle::GetFontStyle("PropertyWindow.NormalFont");
	SlateFontInfo.Size = 8;
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FVector2D SKTimelineFrameRuler::ComputeDesiredSize(float Scale) const
{
	return FVector2D(100.0f, 26.0f);
}

int32 SKTimelineFrameRuler::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                    const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements,
                                    int32 LayerId,
                                    const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 CurrentLayer = LayerId;
	const FVector2D& WidgetSize = AllottedGeometry.GetLocalSize();
	const float ScrollbarWidth = 12.0f;

	FSlateDrawElement::MakeBox(OutDrawElements,
	                           CurrentLayer++,
	                           AllottedGeometry.ToPaintGeometry(),
	                           SlateBrush, ESlateDrawEffect::None);


	TInterval<float> TimeInterval(0, 20.f);
	const TSharedRef<FSlateFontMeasure> FontMeasureService = FSlateApplication::Get().GetRenderer()->
		GetFontMeasureService();
	FNumberFormattingOptions FmtOptions;
	FmtOptions.SetMaximumFractionalDigits(2);
	FmtOptions.SetMinimumFractionalDigits(1);

	const FText MinText = FText::AsNumber(TimeInterval.Min, &FmtOptions);
	const FText MaxText = FText::AsNumber(TimeInterval.Max, &FmtOptions);
	FVector2D MinSize = FontMeasureService->Measure(MinText, SlateFontInfo);
	const FVector2D MaxSize = FontMeasureService->Measure(MaxText, SlateFontInfo);

	float MajorFreq = 0.5f;
	float MinorFreq = 0.25f;
	// Lines
	const float MajorLineSize = WidgetSize.Y * 0.5f;
	const float MinorLineSize = WidgetSize.Y * 0.25f;

	//添加最大值
	const float Padding = MaxSize.X * 0.5f;
	const float MaxPositionX = WidgetSize.X - MaxSize.X * 0.5f - Padding - ScrollbarWidth;
	FVector2D Offset(MaxPositionX, 0);
	FSlateLayoutTransform OffsetTransform = FSlateLayoutTransform(Offset);
	FSlateDrawElement::MakeText(OutDrawElements,
	                            CurrentLayer++,
	                            AllottedGeometry.ToPaintGeometry(OffsetTransform),
	                            MaxText,
	                            SlateFontInfo);

	TArray<FVector2D> Line; // Start/End points.
	Line.SetNum(2);

	Line[0].Y = WidgetSize.Y - 1.0f; // Bottom, minus a bit of padding.
	Line[1].Y = WidgetSize.Y - MajorLineSize;
	//刻度绘制区域
	const float WidgetContentSize = WidgetSize.X - Padding * 2.0f - ScrollbarWidth;

	for (float StepTime = 0.0f; StepTime < TimeInterval.Max + 0.001; StepTime += MajorFreq)
	{
		Line[0].X = Padding + WidgetContentSize * (StepTime / TimeInterval.Max);
		Line[1].X = Line[0].X;

		FSlateDrawElement::MakeLines(OutDrawElements,
		                             CurrentLayer++,
		                             AllottedGeometry.ToPaintGeometry(),
		                             Line);

		{
			FText MajorLabel = FText::AsNumber(StepTime, &FmtOptions);

			Offset.X = Line[0].X - FontMeasureService->Measure(MajorLabel, SlateFontInfo).X * 0.5f;
			OffsetTransform = FSlateLayoutTransform(Offset);

			FSlateDrawElement::MakeText(OutDrawElements,
			                            CurrentLayer++,
			                            AllottedGeometry.ToPaintGeometry(OffsetTransform),
			                            MajorLabel,
			                            SlateFontInfo);
		}
	}

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId + 1, InWidgetStyle,
	                                bParentEnabled);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
