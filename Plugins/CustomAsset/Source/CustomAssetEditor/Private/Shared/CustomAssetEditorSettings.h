// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomAssetEditorSettings.generated.h"

/**
 * 
 */
UCLASS(config=Editor)
class CUSTOMASSETEDITOR_API UCustomAssetEditorSettings : public UObject
{
	GENERATED_BODY()

	public:

	/** Color of the TextAsset editor's background. */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	FSlateColor BackgroundColor;

	/** Color of the TextAsset editor's text. */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	FSlateColor ForegroundColor;

	/** The font to use in the TextAsset editor window. */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	FSlateFontInfo Font;

	/** The margin around the TextAsset editor window (in pixels). */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	float Margin;

	public:

	/** Default constructor. */
	UCustomAssetEditorSettings();
};
