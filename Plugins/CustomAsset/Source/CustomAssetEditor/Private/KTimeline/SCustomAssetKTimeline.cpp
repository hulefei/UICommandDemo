// Fill out your copyright notice in the Description page of Project Settings.


#include "SCustomAssetKTimeline.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCustomAssetKTimeline::Construct(const FArguments& InArgs)
{
	
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
					// SNew(SKSkillSimpleTimelineRuler, InKSkillEditor)
				SNew(SImage).ColorAndOpacity(FColor::Red)
				]
				+ SVerticalBox::Slot()
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						// m_ActionList.ToSharedRef()
						// SimpleTimelineScrollBox.ToSharedRef()
						SNew(SImage).ColorAndOpacity(FColor::Green)
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
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
