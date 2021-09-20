// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	// const FMargin ContentPadding = FMargin(500, 300);
	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot().FillWidth(0.3f)
				[SNew(SButton)]
			+SHorizontalBox::Slot().FillWidth(0.7f)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot().FillHeight(.5f)
						[SNew(SButton)]
					+SVerticalBox::Slot().FillHeight(.5f)
						[SNew(SButton)]
				]
		]
		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot().FillWidth(.2f)
			+SHorizontalBox::Slot().FillWidth(.6f)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().FillHeight(0.2f)
				+SVerticalBox::Slot().FillHeight(0.6f)
					[SNew(SImage).ColorAndOpacity(FColor::Black)]
				+SVerticalBox::Slot().FillHeight(0.2f)
			]
			+SHorizontalBox::Slot().FillWidth(.2f)
		]

		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot().FillWidth(1.0f)
			+SHorizontalBox::Slot().AutoWidth()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().FillHeight(1.0f)
				+SVerticalBox::Slot().AutoHeight()
					[
						SNew(SBox).HeightOverride(128).WidthOverride(128)
						[SNew(SButton)]
					]
				+SVerticalBox::Slot().FillHeight(1.0f)
			]
			+SHorizontalBox::Slot().FillWidth(1.0f)
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
