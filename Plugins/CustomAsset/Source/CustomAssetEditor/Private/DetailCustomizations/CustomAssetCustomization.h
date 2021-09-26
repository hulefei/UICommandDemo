// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IDetailCustomization.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API FCustomAssetCustomization : public IDetailCustomization
{
public:
	FCustomAssetCustomization();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	static TSharedRef<IDetailCustomization> MakeInstance();

private:
	/** Details布局 */
	IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;

};
