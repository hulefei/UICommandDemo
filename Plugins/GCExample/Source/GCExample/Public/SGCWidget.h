// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestUObject.h"
#include "TestFObject.h"

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

	FReply Button1Handle();
	FReply Button2Handle();
	FReply Button3Handle();
	FReply Button4Handle();


	TSharedPtr<FTestFObject> TestFObjectPtr;
	FTestFObject* TestFObject;
	TWeakObjectPtr<UTestUObject> OutWeakObjectPtr;
};
