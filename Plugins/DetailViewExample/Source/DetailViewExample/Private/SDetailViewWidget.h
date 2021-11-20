// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "IDetailsView.h"
class UDetailObject;
/**
 * 
 */
class DETAILVIEWEXAMPLE_API SDetailViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDetailViewWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	FReply OnPlayClicked() const;

private:
	TSharedPtr<IDetailsView> DetailsView;
	UDetailObject* DetailObject = nullptr;

	void OnFinishedChangingProperties(const FPropertyChangedEvent& Event);
	bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;
};
