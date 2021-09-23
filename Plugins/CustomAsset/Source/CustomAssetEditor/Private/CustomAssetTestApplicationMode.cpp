// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetTestApplicationMode.h"

#include "CustomAssetEditorToolbar.h"
#include "CustomAssetSummoner.h"

FCustomAssetTestApplicationMode::FCustomAssetTestApplicationMode(
	TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditor) : FApplicationMode(
	FCustomAssetEditorToolkit::CustomAssetTestMode, FCustomAssetEditorToolkit::GetLocalizedMode)
{
	CustomAssetEditor = InCustomAssetEditor;
	CustomAssetEditorTabFactories.RegisterFactory(MakeShareable(new FCustomAssetSummoner(InCustomAssetEditor)));
	// CustomAssetEditorTabFactories.RegisterFactory(MakeShareable(new FCustomAssetDetailsSummoner(InBehaviorTreeEditor)));
	TabLayout = FTabManager::NewLayout("Standalone_TestEditor_Layout_v2")
		->AddArea(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			                             ->Split(FTabManager::NewStack()
			                                     ->SetSizeCoefficient(0.1f)
			                                     ->AddTab(InCustomAssetEditor->GetToolbarTabId(), ETabState::OpenedTab)
			                                     ->SetHideTabWell(true)));

	InCustomAssetEditor->GetToolbarBuilder()->AddModesToolbar(ToolbarExtender);
}

void FCustomAssetTestApplicationMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();

	CustomAssetEditorPtr->RegisterToolbarTab(InTabManager.ToSharedRef());

	// Mode-specific setup
	CustomAssetEditorPtr->PushTabFactories(CustomAssetEditorTabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FCustomAssetTestApplicationMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();

	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();
}

void FCustomAssetTestApplicationMode::PostActivateMode()
{
	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> BehaviorTreeEditorPtr = CustomAssetEditor.Pin();
	// BehaviorTreeEditorPtr->RestoreBehaviorTree();

	FApplicationMode::PostActivateMode();
}
