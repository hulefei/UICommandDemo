// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetEditorApplicationMode.h"

#include "Toolkits/CustomAssetEditorToolkit.h"


FCustomAssetEditorApplicationMode::FCustomAssetEditorApplicationMode(
	TSharedPtr<FCustomAssetEditorToolkit> InBehaviorTreeEditor) : FApplicationMode(FCustomAssetEditorToolkit::CustomAssetMode, FCustomAssetEditorToolkit::GetLocalizedMode)
{
}

void FCustomAssetEditorApplicationMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();
	
	// CustomAssetEditorPtr->RegisterToolbarTab(InTabManager.ToSharedRef());

	// Mode-specific setup
	CustomAssetEditorPtr->PushTabFactories(CustomAssetEditorTabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FCustomAssetEditorApplicationMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();

	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();
	
	// CustomAssetEditorPtr->SaveEditedObjectState();
}

void FCustomAssetEditorApplicationMode::PostActivateMode()
{
	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> BehaviorTreeEditorPtr = CustomAssetEditor.Pin();
	// BehaviorTreeEditorPtr->RestoreBehaviorTree();

	FApplicationMode::PostActivateMode();
}
