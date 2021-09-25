// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Toolkits/CustomAssetEditorToolkit.h"


/**
 * 
 */
class FCustomAssetEditorToolbar : public TSharedFromThis<FCustomAssetEditorToolbar>
{
public:
	FCustomAssetEditorToolbar(class TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditor)
		: CustomAssetEditor(InCustomAssetEditor)
	{
	}

	void AddModesToolbar(TSharedPtr<FExtender> Extender);
	// void AddDebuggerToolbar(TSharedPtr<FExtender> Extender);
	void AddCustomAssetToolbar(TSharedPtr<FExtender> Extender);

private:
	void FillModesToolbar(FToolBarBuilder& ToolbarBuilder);
	// void FillDebuggerToolbar(FToolBarBuilder& ToolbarBuilder);
	void FillCustomAssetEditorToolbar(FToolBarBuilder& ToolbarBuilder);

protected:
	/** Pointer back to the blueprint editor tool that owns us */
	TWeakPtr<FCustomAssetEditorToolkit> CustomAssetEditor;
};
