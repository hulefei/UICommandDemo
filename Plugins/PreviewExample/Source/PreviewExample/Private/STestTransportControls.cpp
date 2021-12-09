// Fill out your copyright notice in the Description page of Project Settings.


#include "STestTransportControls.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STestTransportControls::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FVector2D STestTransportControls::ComputeDesiredSize(float Scale) const
{
	return FVector2D(100.f, 30.f);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
