// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetKTimelineSummoner.h"
#include "CustomAssetEditorTabs.h"

#define LOCTEXT_NAMESPACE "CustomAssetKTimelineSummoner"

FCustomAssetKTimelineSummoner::FCustomAssetKTimelineSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr)
: FWorkflowTabFactory(FCustomAssetEditorTabs::CustomAssetKTimelineID, InCustomAssetEditorPtr)
	, CustomAssetEditorToolkitPtr(InCustomAssetEditorPtr)
{
	TabLabel = LOCTEXT("CustomPropertiesLabel", "KTimeline");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");
	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("CustomAssetKTimeline", "KTimeline");
	ViewMenuTooltip = LOCTEXT("CustomAssetKTimelineView_ToolTip", "Show the editor view");
}

TSharedRef<SWidget> FCustomAssetKTimelineSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(CustomAssetEditorToolkitPtr.IsValid());
	return CustomAssetEditorToolkitPtr.Pin()->SpawnKTimeline();
}

FText FCustomAssetKTimelineSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("CustomAssetKTimelineTabTooltip", "The Test details tab allows editing of the properties");
}

#undef LOCTEXT_NAMESPACE