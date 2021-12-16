// Fill out your copyright notice in the Description page of Project Settings.


#include "SPreviewTimeline.h"

#include "FrameNumberNumericInterface.h"
#include "SlateOptMacros.h"
#include "Preferences/PersonaOptions.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Layout/SScrollBorder.h"
#include "ITimeSlider.h"
#include "EditorStyleSet.h"
#include "ISequencerWidgetsModule.h"
#include "PreviewTimeSliderController.h"
#include "SPreviewOutliner.h"
#include "SPreviewTrackArea.h"
#include "Styling/ISlateStyle.h"
#include "Styling/SlateTypes.h"

#define LOCTEXT_NAMESPACE "SPreviewTimeline"

void SPreviewTimeline::Construct(const FArguments& InArgs)
{

	ColumnFillCoefficients[0] = 0.2f;
	ColumnFillCoefficients[1] = 0.8f;

	TAttribute<FAnimatedRange> ViewRange = MakeAttributeLambda([](){ return FAnimatedRange(0.0, 100.0); });
	FTimeSliderArgs TimeSliderArgs;
	{
		TimeSliderArgs.ViewRange = ViewRange;
	}
	TimeSliderController = MakeShareable(new FPreviewTimeSliderController(TimeSliderArgs, SharedThis(this), SecondaryNumericTypeInterface));
	
	TSharedRef<FPreviewTimeSliderController> TimeSliderControllerRef = TimeSliderController.ToSharedRef();

	TSharedRef<SScrollBar> ScrollBar = SNew(SScrollBar)
		.Thickness(FVector2D(5.0f, 5.0f));
	
	// Create the top slider
	const bool bMirrorLabels = false;
	ISequencerWidgetsModule& SequencerWidgets = FModuleManager::Get().LoadModuleChecked<ISequencerWidgetsModule>("SequencerWidgets");
	TopTimeSlider = SequencerWidgets.CreateTimeSlider(TimeSliderControllerRef, bMirrorLabels);

	TrackArea = SNew(SPreviewTrackArea, TimeSliderControllerRef);
	Outliner = SNew(SPreviewOutliner, TrackArea.ToSharedRef())
		// .ExternalScrollbar(ScrollBar)
		.Clipping(EWidgetClipping::ClipToBounds);
		// .FilterText_Lambda([this](){ return FilterText; });

	// TrackArea->SetOutliner(Outliner);

	int32 SequenceFrameRate = 30;//FMath::RoundToInt(InModel->GetFrameRate());
	int32 TickResolutionValue = FMath::RoundToInt((double)GetDefault<UPersonaOptions>()->TimelineScrubSnapValue * SequenceFrameRate);//InModel->GetTickResolution();

	TAttribute<float> FillCoefficient_0, FillCoefficient_1;
	{
		FillCoefficient_0.Bind(TAttribute<float>::FGetter::CreateSP(this, &SPreviewTimeline::GetColumnFillCoefficient, 0));
		FillCoefficient_1.Bind(TAttribute<float>::FGetter::CreateSP(this, &SPreviewTimeline::GetColumnFillCoefficient, 1));
	}

	const int32 Column0 = 0, Column1 = 1;
	const int32 Row0 = 0, Row1 = 1, Row2 = 2, Row3 = 3, Row4 = 4;

	const float CommonPadding = 3.f;
	const FMargin ResizeBarPadding(4.f, 0, 0, 0);

	TAttribute<EFrameNumberDisplayFormats> DisplayFormat = MakeAttributeLambda([]()
	{
		return GetDefault<UPersonaOptions>()->TimelineDisplayFormat;
	});

	TAttribute<EFrameNumberDisplayFormats> DisplayFormatSecondary = MakeAttributeLambda([]()
	{
		return GetDefault<UPersonaOptions>()->TimelineDisplayFormat == EFrameNumberDisplayFormats::Frames ? EFrameNumberDisplayFormats::Seconds : EFrameNumberDisplayFormats::Frames;
	});

	TAttribute<FFrameRate> TickResolution = MakeAttributeLambda([TickResolutionValue]()
	{
		return FFrameRate(TickResolutionValue, 1);
	});

	TAttribute<FFrameRate> DisplayRate = MakeAttributeLambda([SequenceFrameRate]()
	{
		return FFrameRate(SequenceFrameRate, 1);
	});
	
	// Create our numeric type interface so we can pass it to the time slider below.
	NumericTypeInterface = MakeShareable(new FFrameNumberInterface(DisplayFormat, 0, TickResolution, DisplayRate));
	SecondaryNumericTypeInterface = MakeShareable(new FFrameNumberInterface(DisplayFormatSecondary, 0, TickResolution, DisplayRate));

	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				[
					SNew(SGridPanel)
					.FillRow(1, 1.0f)
					.FillColumn(0, FillCoefficient_0)
					.FillColumn(1, FillCoefficient_1)

					// outliner search box
					+SGridPanel::Slot(Column0, Row0, SGridPanel::Layer(10))
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						[
							SAssignNew(SearchBox, SSearchBox)
							.HintText(LOCTEXT("FilterTracksHint", "Filter"))
							// .OnTextChanged(this, &SAnimTimeline::OnOutlinerSearchChanged)
						]
						+SHorizontalBox::Slot()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.AutoWidth()
						.Padding(2.0f, 0.0f, 2.0f, 0.0f)
						[
							SNew(SBox)
							.MinDesiredWidth(30.0f)
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Center)
							[
								// Current Play Time 
								SNew(SSpinBox<double>)
								.Style(&FEditorStyle::GetWidgetStyle<FSpinBoxStyle>("Sequencer.PlayTimeSpinBox"))
								.Value_Lambda([this]() -> double
								{
									return 0;
									// return Model.Pin()->GetScrubPosition().Value;
								})
								// .OnValueChanged(this, &SAnimTimeline::SetPlayTime)
								.OnValueCommitted_Lambda([this](double InFrame, ETextCommit::Type)
								{
									// SetPlayTime(InFrame);
								})
								.MinValue(TOptional<double>())
								.MaxValue(TOptional<double>())
								.TypeInterface(NumericTypeInterface)
								// .Delta(this, &SAnimTimeline::GetSpinboxDelta)
								.LinearDeltaSensitivity(25)
							]
						]
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
							SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::White))
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
								// 			// Outliner.ToSharedRef()
								// 			SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::Black))
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
								// 			// TrackArea.ToSharedRef()
								// 			SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::White))
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
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					[
						// SNew(SAnimTimelineTransportControls, InModel->GetPreviewScene(), InModel->GetAnimSequenceBase())
						SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::Red))
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
							TopTimeSlider.ToSharedRef()
						]
					]

					// Overlay that draws the tick lines
					+SGridPanel::Slot(Column1, Row1, SGridPanel::Layer(10))
					.Padding(ResizeBarPadding)
					[
						SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::Blue))
						// SNew(SAnimTimelineOverlay, TimeSliderControllerRef)
						// .Visibility( EVisibility::HitTestInvisible )
						// .DisplayScrubPosition( false )
						// .DisplayTickLines( true )
						// .Clipping(EWidgetClipping::ClipToBounds)
						// .PaintPlaybackRangeArgs(FPaintPlaybackRangeArgs(FEditorStyle::GetBrush("Sequencer.Timeline.PlayRange_L"), FEditorStyle::GetBrush("Sequencer.Timeline.PlayRange_R"), 6.f))
					]

					// Overlay that draws the scrub position
					+SGridPanel::Slot(Column1, Row1, SGridPanel::Layer(20))
					.Padding(ResizeBarPadding)
					[
					SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::Yellow))
						// SNew(SAnimTimelineOverlay, TimeSliderControllerRef)
						// .Visibility( EVisibility::HitTestInvisible )
						// .DisplayScrubPosition( true )
						// .DisplayTickLines( false )
						// .Clipping(EWidgetClipping::ClipToBounds)
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
							// BottomTimeRange
							SNew(SImage).ColorAndOpacity(FSlateColor(FLinearColor::Gray))
						]
					]
				]
				+SOverlay::Slot()
				[
					// track area virtual splitter overlay
					// SNew(SAnimTimelineSplitterOverlay)
					SNew(SSplitter)
					.Style(FEditorStyle::Get(), "AnimTimeline.Outliner.Splitter")
					.Visibility(EVisibility::SelfHitTestInvisible)
				
					+ SSplitter::Slot()
					.Value(FillCoefficient_0)
					.OnSlotResized(SSplitter::FOnSlotResized::CreateSP(this, &SPreviewTimeline::OnColumnFillCoefficientChanged, 0))
					[
						SNew(SSpacer)
					]
				
					+ SSplitter::Slot()
					.Value(FillCoefficient_1)
					.OnSlotResized(SSplitter::FOnSlotResized::CreateSP(this, &SPreviewTimeline::OnColumnFillCoefficientChanged, 1))
					[
						SNew(SSpacer)
					]
				]
			]
		]
	];
}

void SPreviewTimeline::OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex)
{
	ColumnFillCoefficients[ColumnIndex] = FillCoefficient;
}

#undef LOCTEXT_NAMESPACE
