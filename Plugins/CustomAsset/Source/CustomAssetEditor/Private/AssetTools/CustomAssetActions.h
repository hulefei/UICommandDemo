// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AssetTypeActions_Base.h"
#include "Toolkits/CustomAssetEditorToolkit.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API FCustomAssetActions : public FAssetTypeActions_Base
{
public:
	FCustomAssetActions();
	// void CreateBlueprint();

	public:
	//~ FAssetTypeActions_Base overrides
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual  UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;

	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;

private:

	/** Pointer to the style set to use for toolkits. */
	// TSharedRef<ISlateStyle> Style;

	void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor);
};
