// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetTimelineSummoner.h"
#include "CustomAssetEditorTabs.h"

#define LOCTEXT_NAMESPACE "CustomAssetTimelineSummoner"

FCustomAssetTimelineSummoner::FCustomAssetTimelineSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr)
: FWorkflowTabFactory(FCustomAssetEditorTabs::CustomAssetTimelineID, InCustomAssetEditorPtr)
	, CustomAssetEditorToolkitPtr(InCustomAssetEditorPtr)
{
	TabLabel = LOCTEXT("CustomPropertiesLabel", "Timeline");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");
	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("CustomEditorView", "Timeline");
	ViewMenuTooltip = LOCTEXT("CustomEditorView_ToolTip", "Show the editor view");
}

TSharedRef<SWidget> FCustomAssetTimelineSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(CustomAssetEditorToolkitPtr.IsValid());
	return CustomAssetEditorToolkitPtr.Pin()->SpawnTimeline();
}

FText FCustomAssetTimelineSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("CustomEditorDetailsTabTooltip", "The Test details tab allows editing of the properties");
}

#undef LOCTEXT_NAMESPACE
