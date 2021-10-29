// Fill out your copyright notice in the Description page of Project Settings.


#include "SCustomAssetTimeline.h"

#include "SlateOptMacros.h"
#include "Widgets/Layout/SGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCustomAssetTimeline::Construct(const FArguments& InArgs)
{
	int32 TickResolutionValue = 60;//InModel->GetTickResolution();
	int32 SequenceFrameRate = 30;//FMath::RoundToInt(InModel->GetFrameRate());
	
	TSharedRef<SScrollBar> ScrollBar = SNew(SScrollBar)
		.Thickness(FVector2D(5.0f, 5.0f));
	
	ColumnFillCoefficients[0] = 0.2f;
	ColumnFillCoefficients[1] = 0.8f;

	TAttribute<float> FillCoefficient_0, FillCoefficient_1;
	{
		FillCoefficient_0.Bind(
			TAttribute<float>::FGetter::CreateSP(this, &SCustomAssetTimeline::GetColumnFillCoefficient, 0));
		FillCoefficient_1.Bind(
			TAttribute<float>::FGetter::CreateSP(this, &SCustomAssetTimeline::GetColumnFillCoefficient, 1));
	}
	
	const int32 Column0 = 0, Column1 = 1;
	const int32 Row0 = 0, Row1 = 1, Row2 = 2, Row3 = 3, Row4 = 4;

	const float CommonPadding = 3.f;
	const FMargin ResizeBarPadding(4.f, 0, 0, 0);
	
	ChildSlot
	[
		// SNew(STextBlock).Text(FText::FromString(TEXT("SKSkillTimeline")))
		// SNew(SImage).ColorAndOpacity(FColor::Black)
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SGridPanel)
					.FillRow(1, 1.0f)
					.FillColumn(0, FillCoefficient_0)
					.FillColumn(1, FillCoefficient_1)
					
					// outliner search box
					+SGridPanel::Slot(Column0, Row0, SGridPanel::Layer(10))
					[
						SNew(SImage).ColorAndOpacity(FColor::Red)
					]

					// main timeline area
					+SGridPanel::Slot(Column0, Row1, SGridPanel::Layer(10))
					.ColumnSpan(2)
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						[
							SNew(SOverlay)
							+SOverlay::Slot()
							[
								//Tree
								SNew(SImage).ColorAndOpacity(FColor::Blue)
								// SNew(SScrollBorder, Outliner.ToSharedRef())
								// [
								// 	SNew(SHorizontalBox)
								//
								// 	// outliner tree
								// 	+SHorizontalBox::Slot()
								// 	.FillWidth(FillCoefficient_0)
								// 	[
								// 		SNew(SBox)
								// 		[
								// 			Outliner.ToSharedRef()
								// 		]
								// 	]
								//
								// 	// track area
								// 	+SHorizontalBox::Slot()
								// 	.FillWidth(FillCoefficient_1)
								// 	[
								// 		SNew(SBox)
								// 		.Padding(ResizeBarPadding)
								// 		.Clipping(EWidgetClipping::ClipToBounds)
								// 		[
								// 			TrackArea.ToSharedRef()
								// 		]
								// 	]
								// ]
							]

							+SOverlay::Slot()
							.HAlign(HAlign_Right)
							[
								ScrollBar
							]
						]
					]

					// Transport controls
					+SGridPanel::Slot(Column0, Row3, SGridPanel::Layer(10))
					// .VAlign(VAlign_Center)
					// .HAlign(HAlign_Center)
					[
						// SNew(SAnimTimelineTransportControls, InModel->GetPreviewScene(), InModel->GetAnimSequenceBase())
						SNew(SImage).ColorAndOpacity(FColor::Orange)
					]

					// Second column
					+SGridPanel::Slot(Column1, Row0)
					.Padding(ResizeBarPadding)
					.RowSpan(2)
					[
						SNew(SBorder)
						.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
						[
							SNew(SSpacer)
						]
					]

					+SGridPanel::Slot(Column1, Row0, SGridPanel::Layer(10))
					.Padding(ResizeBarPadding)
					[
						SNew( SBorder )
						.BorderImage( FEditorStyle::GetBrush("ToolPanel.GroupBorder") )
						.BorderBackgroundColor( FLinearColor(.50f, .50f, .50f, 1.0f ) )
						.Padding(0)
						.Clipping(EWidgetClipping::ClipToBounds)
						[
							// TopTimeSlider.ToSharedRef()
							SNew(SImage).ColorAndOpacity(FColor::Yellow)
						]
					]

					// Overlay that draws the tick lines
					+SGridPanel::Slot(Column1, Row1, SGridPanel::Layer(10))
					.Padding(ResizeBarPadding)
					[
						// SNew(SAnimTimelineOverlay, TimeSliderControllerRef)
						SNew(SImage).ColorAndOpacity(FColor::Green)
						.Visibility( EVisibility::HitTestInvisible )
						// .DisplayScrubPosition( false )
						// .DisplayTickLines( true )
						// .Clipping(EWidgetClipping::ClipToBounds)
						// .PaintPlaybackRangeArgs(FPaintPlaybackRangeArgs(FEditorStyle::GetBrush("Sequencer.Timeline.PlayRange_L"), FEditorStyle::GetBrush("Sequencer.Timeline.PlayRange_R"), 6.f))
					]

					// play range slider
					+SGridPanel::Slot(Column1, Row3, SGridPanel::Layer(10))
					.Padding(ResizeBarPadding)
					[
						SNew(SBorder)
						.BorderImage( FEditorStyle::GetBrush("ToolPanel.GroupBorder") )
						.BorderBackgroundColor( FLinearColor(0.5f, 0.5f, 0.5f, 1.0f ) )
						.Clipping(EWidgetClipping::ClipToBounds)
						.Padding(0)
						[
							SNew(SImage).ColorAndOpacity(FColor::Cyan)
							// BottomTimeRange
						]
					]
				]

				//custom Sliptter overlay
				// +SOverlay::Slot()
				// [
					// track area virtual splitter overlay
					// SNew(SAnimTimelineSplitterOverlay)
					// SNew(SOverlay)
					// .Style(FEditorStyle::Get(), "AnimTimeline.Outliner.Splitter")
					// .Visibility(EVisibility::SelfHitTestInvisible)
					//
					// + SSplitter::Slot()
					// .Value(FillCoefficient_0)
					// // .OnSlotResized(SSplitter::FOnSlotResized::CreateSP(this, &SAnimTimeline::OnColumnFillCoefficientChanged, 0))
					// [
					// 	SNew(SSpacer)
					// ]

					// + SSplitter::Slot()
					// .Value(FillCoefficient_1)
					// .OnSlotResized(SSplitter::FOnSlotResized::CreateSP(this, &SAnimTimeline::OnColumnFillCoefficientChanged, 1))
					// [
					// 	SNew(SSpacer)
					// ]
				// ]
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
