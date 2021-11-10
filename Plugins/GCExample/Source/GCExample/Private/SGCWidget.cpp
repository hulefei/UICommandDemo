// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SGCWidget::Button1Handle()
{
	TestFObject = new FTestFObject();
	OutWeakObjectPtr = TestFObject->TestUObject;
	// TestUObject->AddToRoot();
	
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("init")));
	return FReply::Handled();
}

FReply SGCWidget::Button2Handle()
{
	CollectGarbage(EObjectFlags::RF_NoFlags);
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("GC")));
	return FReply::Handled();
}

FReply SGCWidget::Button3Handle()
{
	if (TestFObject != nullptr)
	{
		if (OutWeakObjectPtr.IsValid())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("TestFObject not nullptr : Valid")));
		} else
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("TestFObject not nullptr : not Valid")));
		}
	} else
	{
		if (OutWeakObjectPtr.IsValid())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("TestFObject is nullptr: Valid")));
		} else
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("TestFObject is nullptr : not Valid")));
		}
	}
	
	return FReply::Handled();
}

FReply SGCWidget::Button4Handle()
{
	delete TestFObject;
	CollectGarbage(EObjectFlags::RF_NoFlags);
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("delete TestFObject")));
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
