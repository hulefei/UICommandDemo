// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class GCEXAMPLE_API SGCWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGCWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply Button1Handle() const;
	FReply Button2Handle() const;
	FReply Button3Handle() const;
	FReply Button4Handle() const;
};
