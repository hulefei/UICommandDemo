// Fill out your copyright notice in the Description page of Project Settings.


#include "SPreStudyWidget.h"
#include "Widgets/Layout/SGridPanel.h"

#include "SlateOptMacros.h"
#include "Reflection/ReflectionObject.h"

#define LOCTEXT_NAMESPACE "SPreStudyWidget"

void SPreStudyWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SGridPanel)
			.FillRow(1, 1.0f)
			+ SGridPanel::Slot(0, 0, SGridPanel::Layer(10))
			[
				SNew(SButton).Text(LOCTEXT("Reflection", "Reflection")).OnClicked_Lambda([this]() -> FReply
				{
					UReflectionObject::Main();
					return FReply::Handled();
				})
			]
			+ SGridPanel::Slot(1, 0, SGridPanel::Layer(10))
			[
				SNew(SButton)
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE
