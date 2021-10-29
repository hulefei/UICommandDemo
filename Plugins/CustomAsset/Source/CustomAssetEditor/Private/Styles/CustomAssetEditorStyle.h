// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Styling/SlateStyle.h"

class FCustomAssetEditorStyle
{
public:
	FCustomAssetEditorStyle();
	virtual ~FCustomAssetEditorStyle();

	static ISlateStyle& Get();

	static void Initialize();
	
	static void Shutdown();
	
	static FName GetStyleSetName();

	static const FSlateBrush* GetBrush(FName BrushName);

	static void ReloadTextures();

private:
	static TSharedPtr<FSlateStyleSet> Singleton;
	static TSharedRef< FSlateStyleSet > Create();
};

