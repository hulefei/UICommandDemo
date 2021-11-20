// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "IDetailsView.h"
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

private:
	TSharedPtr<IDetailsView> DetailsView;
};
