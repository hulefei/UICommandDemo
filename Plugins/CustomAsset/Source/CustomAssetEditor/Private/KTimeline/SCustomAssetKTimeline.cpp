// Fill out your copyright notice in the Description page of Project Settings.


#include "SCustomAssetKTimeline.h"

#include "SCustomAssetKTimelineScrollBox.h"
#include "SlateOptMacros.h"
#include "SKTimelineRuler.h"
#include "SKTimelineTrack.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCustomAssetKTimeline::Construct(const FArguments& InArgs)
{
	KTimelineScrollBox = SNew(SCustomAssetKTimelineScrollBox);
	
	ChildSlot
	[
		// Populate the widget
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(0.98f)
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.VAlign(EVerticalAlignment::VAlign_Top)
				[
					SNew(SKTimelineRuler)
				// SNew(SImage).ColorAndOpacity(FColor::Red)
				]
				+ SVerticalBox::Slot()
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						// m_ActionList.ToSharedRef()
						KTimelineScrollBox.ToSharedRef()
						// SNew(SImage).ColorAndOpacity(FColor::Green)
					]
					// + SOverlay::Slot()
					// [
					// 	SNew(STextBlock)
					// .Text(LOCTEXT("FSKTimelinePanelNoSegment", "未选中片段节点"))
					// .Visibility_Raw(this, &SSKTimelinePanel::CheckSegmentEmpty)
					// ]
				]
			]
		]
	];


	UpdateTrack();
}

void SCustomAssetKTimeline::UpdateTrack() const
{
	KTimelineScrollBox->AddSlot()
						.VAlign(VAlign_Top)
						.Padding(0, 0.0f)
	[
		SNew(SKTimelineTrack)
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
