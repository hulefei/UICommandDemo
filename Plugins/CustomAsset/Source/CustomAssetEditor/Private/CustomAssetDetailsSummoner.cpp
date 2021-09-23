// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetDetailsSummoner.h"

#include "CustomAssetEditorTabs.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditorFactories"

FCustomAssetDetailsSummoner::FCustomAssetDetailsSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr)
: FWorkflowTabFactory(FCustomAssetEditorTabs::CustomAssetDetailsID, InCustomAssetEditorPtr)
	, CustomAssetEditorToolkitPtr(InCustomAssetEditorPtr)
{
	TabLabel = LOCTEXT("CustomEditorLabel", "Properties");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");
	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("CustomEditorView", "Details");
	ViewMenuTooltip = LOCTEXT("CustomEditorView_ToolTip", "Show the editor view");
}

TSharedRef<SWidget> FCustomAssetDetailsSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(CustomAssetEditorToolkitPtr.IsValid());
	return CustomAssetEditorToolkitPtr.Pin()->SpawnProperties();
}

FText FCustomAssetDetailsSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("CustomEditorDetailsTabTooltip", "The Test details tab allows editing of the properties");
}

#undef LOCTEXT_NAMESPACE
