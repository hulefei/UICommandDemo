// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetSummoner.h"

#include "CustomAssetEditorTabs.h"
#include "Toolkits/CustomAssetEditorToolkit.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditorFactories"

FCustomAssetSummoner::FCustomAssetSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr)
	: FWorkflowTabFactory(FCustomAssetEditorTabs::GraphDetailsID, InCustomAssetEditorPtr)
	, CustomAssetEditorToolkitPtr(InCustomAssetEditorPtr)
{
	TabLabel = LOCTEXT("TestDetailsLabel", "Details");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");
	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("TestDetailsView", "Details");
	ViewMenuTooltip = LOCTEXT("TestDetailsView_ToolTip", "Show the details view");
}

TSharedRef<SWidget> FCustomAssetSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(CustomAssetEditorToolkitPtr.IsValid());
	return CustomAssetEditorToolkitPtr.Pin()->SpawnProperties();
}

FText FCustomAssetSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("TestDetailsTabTooltip", "The Test details tab allows editing of the properties");
}

#undef LOCTEXT_NAMESPACE