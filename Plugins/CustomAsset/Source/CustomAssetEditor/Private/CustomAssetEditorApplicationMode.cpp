// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetEditorApplicationMode.h"

#include "CustomAssetDetailsSummoner.h"
#include "CustomAssetEditorTabs.h"
#include "CustomAssetSummoner.h"
#include "Toolkits/CustomAssetEditorToolkit.h"


FCustomAssetEditorApplicationMode::FCustomAssetEditorApplicationMode(
	TSharedPtr<FCustomAssetEditorToolkit> InBehaviorTreeEditor) : FApplicationMode(FCustomAssetEditorToolkit::CustomAssetMode, FCustomAssetEditorToolkit::GetLocalizedMode)
{
	CustomAssetEditor = InBehaviorTreeEditor;
	CustomAssetEditorTabFactories.RegisterFactory(MakeShareable(new FCustomAssetSummoner(InBehaviorTreeEditor)));
	CustomAssetEditorTabFactories.RegisterFactory(MakeShareable(new FCustomAssetDetailsSummoner(InBehaviorTreeEditor)));

	TabLayout = FTabManager::NewLayout( "Standalone_TestEditor_Layout_v1" )
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.8f)
			->AddTab(FCustomAssetEditorTabs::CustomAssetEditorID, ETabState::OpenedTab)
			->SetHideTabWell(true) 
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.2f)
			->AddTab(FCustomAssetEditorTabs::CustomAssetDetailsID, ETabState::OpenedTab)
			->SetHideTabWell(true) 
		)
	);
}

void FCustomAssetEditorApplicationMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();
	
	CustomAssetEditorPtr->RegisterToolbarTab(InTabManager.ToSharedRef());

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
