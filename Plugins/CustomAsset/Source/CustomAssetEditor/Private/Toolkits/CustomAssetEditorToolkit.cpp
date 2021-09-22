// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "Widgets/SCustomAssetEditor.h"
#include "CustomAsset.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FTextAssetEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogTextAssetEditor, Log, All);


/* Local constants
 *****************************************************************************/

namespace TextAssetEditor
{
	static const FName AppIdentifier("TextAssetEditorApp");
	static const FName TabId("TextEditor");
}


/* FTextAssetEditorToolkit structors
 *****************************************************************************/

FCustomAssetEditorToolkit::FCustomAssetEditorToolkit(const TSharedRef<ISlateStyle>& InStyle)
	: CustomAsset(nullptr)
	, Style(InStyle)
{ }


FCustomAssetEditorToolkit::~FCustomAssetEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}


/* FTextAssetEditorToolkit interface
 *****************************************************************************/

void FCustomAssetEditorToolkit::Initialize(UCustomAsset* InCustomAsset, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost)
{
	CustomAsset = InCustomAsset;

	// Support undo/redo
	CustomAsset->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_CustomAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewSplitter()
						->SetOrientation(Orient_Vertical)
						->SetSizeCoefficient(0.66f)
						->Split
						(
							FTabManager::NewStack()
								->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
								->SetHideTabWell(true)
								->SetSizeCoefficient(0.1f)
								
						)
						->Split
						(
							FTabManager::NewStack()
								->AddTab(TextAssetEditor::TabId, ETabState::OpenedTab)
								->SetHideTabWell(true)
								->SetSizeCoefficient(0.9f)
						)
				)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		TextAssetEditor::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InCustomAsset
	);

	RegenerateMenusAndToolbars();
}


/* FAssetEditorToolkit interface
 *****************************************************************************/

FString FCustomAssetEditorToolkit::GetDocumentationLink() const
{
	return FString(TEXT("https://github.com/ue4plugins/TextAsset"));
}


void FCustomAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CustomAssetEditor", "Custom Asset Editor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(TextAssetEditor::TabId, FOnSpawnTab::CreateSP(this, &FCustomAssetEditorToolkit::HandleTabManagerSpawnTab, TextAssetEditor::TabId))
		.SetDisplayName(LOCTEXT("CustomEditorTabName", "Custom Editor"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}


void FCustomAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(TextAssetEditor::TabId);
}


/* IToolkit interface
 *****************************************************************************/

FText FCustomAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Asset Editor");
}


FName FCustomAssetEditorToolkit::GetToolkitFName() const
{
	return FName("CustomAssetEditor");
}


FLinearColor FCustomAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}


FString FCustomAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "CustomAsset ").ToString();
}


/* FGCObject interface
 *****************************************************************************/

void FCustomAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(CustomAsset);
}


/* FEditorUndoClient interface
*****************************************************************************/

void FCustomAssetEditorToolkit::PostUndo(bool bSuccess)
{ }


void FCustomAssetEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}


/* FTextAssetEditorToolkit callbacks
 *****************************************************************************/

TSharedRef<SDockTab> FCustomAssetEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == TextAssetEditor::TabId)
	{
		TabWidget = SNew(SCustomAssetEditor, CustomAsset, Style);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}


#undef LOCTEXT_NAMESPACE
