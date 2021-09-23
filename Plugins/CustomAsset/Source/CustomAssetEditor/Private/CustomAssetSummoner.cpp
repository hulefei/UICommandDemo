// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetSummoner.h"

#include "CustomAssetEditorTabs.h"
#include "Toolkits/CustomAssetEditorToolkit.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditorFactories"

FCustomAssetSummoner::FCustomAssetSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr)
	: FWorkflowTabFactory(FCustomAssetEditorTabs::CustomAssetEditorID, InCustomAssetEditorPtr)
	, CustomAssetEditorToolkitPtr(InCustomAssetEditorPtr)
{
	TabLabel = LOCTEXT("CustomEditorLabel", "Editor");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");
	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("CustomEditorView", "Details");
	ViewMenuTooltip = LOCTEXT("CustomEditorView_ToolTip", "Show the editor view");
}

TSharedRef<SWidget> FCustomAssetSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(CustomAssetEditorToolkitPtr.IsValid());
	return CustomAssetEditorToolkitPtr.Pin()->SpawnEditable();
}

FText FCustomAssetSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("CustomEditorTabTooltip", "The Test details tab allows editing of the properties");
}

#undef LOCTEXT_NAMESPACE