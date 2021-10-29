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

	const float Padding = MaxSize.X * 0.5f;
	const float MaxPositionX = WidgetSize.X - MaxSize.X * 0.5f - Padding - ScrollbarWidth;
	// Right side (Max Time Label)
	const FSlateLayoutTransform Transform = FSlateLayoutTransform(FVector2D(MaxPositionX, 0));
	FSlateDrawElement::MakeText(OutDrawElements,
	                            CurrentLayer++,
	                            AllottedGeometry.ToPaintGeometry(Transform),
	                            MaxText,
	                            SlateFontInfo);
	

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId + 1, InWidgetStyle,
	                                bParentEnabled);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
