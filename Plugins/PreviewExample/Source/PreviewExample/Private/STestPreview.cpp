// Fill out your copyright notice in the Description page of Project Settings.


#include "STestPreview.h"

#include "SlateOptMacros.h"
#include "SPreviewTimeline.h"
#include "STestTransportControls.h"
#include "STestEditorViewport.h"
#include "TestEditorViewportClient.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STestPreview::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.FillHeight(.5f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .FillHeight(1.f)
			  .HAlign(HAlign_Fill)
			[
				SAssignNew(TestEditorViewport, STestEditorViewport)
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Fill)
				  .VAlign(VAlign_Fill)
				  .FillWidth(1)
				  .Padding(FMargin(0.0f, 0.0f))
				[
					SNew(SBorder)
				]

				// Padding
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					// Padding to make controls line up with the track label widths.
					// note: a more robust way to accomplish this would be nice.
					SNew(SSpacer)
					.Size(FVector2D(16.0f, 16.0f))
				]

				// SKSkillTimelineTransportControls
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(TestTransportControls, STestTransportControls)
				]
			]
		]

		+ SVerticalBox::Slot()
		.FillHeight(.5f)
		[
			SNew(SPreviewTimeline)
		]
	];

	TestTransportControls->SetTestEditorViewportClient(
		StaticCastSharedPtr<FTestEditorViewportClient>(TestEditorViewport->GetViewportClient()));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
