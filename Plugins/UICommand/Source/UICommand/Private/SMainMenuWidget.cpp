// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"

#include "MenuHUD.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;
	
	ChildSlot
	[
		// Populate the widget
		SNew(SButton).OnClicked(this, &SMainMenuWidget::OnPlayClicked)
	];
}

FReply SMainMenuWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveMenu();
	}

	return FReply::Handled();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
