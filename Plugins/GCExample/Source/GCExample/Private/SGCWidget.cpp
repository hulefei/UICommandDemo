// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SGCWidget::Button1Handle() const
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Button1Handle")));
	return FReply::Handled();
}

FReply SGCWidget::Button2Handle() const
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Button2Handle")));
	return FReply::Handled();
}

FReply SGCWidget::Button3Handle() const
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Button3Handle")));
	return FReply::Handled();
}

FReply SGCWidget::Button4Handle() const
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Button4Handle")));
	return FReply::Handled();
}

void SGCWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		// Populate the widget
		SNew(SBox).HeightOverride(500).WidthOverride(500)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.5)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().FillHeight(0.5f)
				[
					SNew(SButton).Text(FText::FromString(TEXT("Button1"))).OnClicked(
						FOnClicked::CreateSP(this, &SGCWidget::Button1Handle))
				]
				+ SVerticalBox::Slot().FillHeight(0.5f)
				[
					SNew(SButton).Text(FText::FromString(TEXT("Button2"))).OnClicked(
						FOnClicked::CreateSP(this, &SGCWidget::Button2Handle))
				]
			]
			+ SHorizontalBox::Slot().FillWidth(0.5)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().FillHeight(0.5f)
				[
					SNew(SButton).Text(FText::FromString(TEXT("Button3"))).OnClicked(
						FOnClicked::CreateSP(this, &SGCWidget::Button3Handle))
				]
				+ SVerticalBox::Slot().FillHeight(0.5f)
				[
					SNew(SButton).Text(FText::FromString(TEXT("Button4"))).OnClicked(
						FOnClicked::CreateSP(this, &SGCWidget::Button4Handle))
				]
			]
		]


	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
