// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "Widgets/SCustomAssetEditor.h"
#include "CustomAsset.h"
#include "CustomAssetEditorApplicationMode.h"
#include "CustomAssetEditorToolbar.h"
#include "CustomAssetTestApplicationMode.h"
#include "CustomAssetSummoner.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogCustomAssetEditor, Log, All);

const FName FCustomAssetEditorToolkit::CustomAssetMode(TEXT("CustomAsset"));
const FName FCustomAssetEditorToolkit::CustomAssetTestMode(TEXT("CustomAssetTestMode"));

/* Local constants
 *****************************************************************************/

namespace CustomAssetEditor
{
	static const FName AppIdentifier("CustomAssetEditorApp");
	static const FName TabId("CustomEditor");
}


/* FTextAssetEditorToolkit structors
 *****************************************************************************/

FCustomAssetEditorToolkit::FCustomAssetEditorToolkit(const TSharedRef<ISlateStyle>& InStyle)
	: CustomAsset(nullptr)
	  , Style(InStyle)
{
	
}


FCustomAssetEditorToolkit::~FCustomAssetEditorToolkit()
{
	// FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	// FReimportManager::Instance()->OnPostReimport().RemoveAll(this);
	//
	// GEditor->UnregisterForUndo(this);
}


/* FTextAssetEditorToolkit interface
 *****************************************************************************/

// void FCustomAssetEditorToolkit::Initialize(UCustomAsset* InCustomAsset, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost)
// {
// 	CustomAsset = InCustomAsset;
//
// 	// Support undo/redo
// 	CustomAsset->SetFlags(RF_Transactional);
// 	GEditor->RegisterForUndo(this);
//
// 	// create tab layout
// 	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_CustomAssetEditor")
// 		->AddArea
// 		(
// 			FTabManager::NewPrimaryArea()
// 				->SetOrientation(Orient_Horizontal)
// 				->Split
// 				(
// 					FTabManager::NewSplitter()
// 						->SetOrientation(Orient_Vertical)
// 						->SetSizeCoefficient(0.66f)
// 						->Split
// 						(
// 							FTabManager::NewStack()
// 								->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
// 								->SetHideTabWell(true)
// 								->SetSizeCoefficient(0.1f)
// 								
// 						)
// 						->Split
// 						(
// 							FTabManager::NewStack()
// 								->AddTab(TextAssetEditor::TabId, ETabState::OpenedTab)
// 								->SetHideTabWell(true)
// 								->SetSizeCoefficient(0.9f)
// 						)
// 				)
// 		);
//
// 	FAssetEditorToolkit::InitAssetEditor(
// 		InMode,
// 		InToolkitHost,
// 		TextAssetEditor::AppIdentifier,
// 		Layout,
// 		true /*bCreateDefaultStandaloneMenu*/,
// 		true /*bCreateDefaultToolbar*/,
// 		InCustomAsset
// 	);
//
// 	RegenerateMenusAndToolbars();
// }

void FCustomAssetEditorToolkit::Initialize(UCustomAsset* InCustomAsset, const EToolkitMode::Type InMode,
                                           const TSharedPtr<class IToolkitHost>& InToolkitHost)
{
	CustomAsset = InCustomAsset;

	if (!ToolbarBuilder.IsValid())
	{
		ToolbarBuilder = MakeShareable(new FCustomAssetEditorToolbar(SharedThis(this)));
	}

	CreateInternalWidgets();
	// TSharedPtr<FCustomAssetEditorToolkit> ThisPtr(SharedThis(this));
	// if(!DocumentManager.IsValid())
	// {
	// 	DocumentManager = MakeShareable(new FDocumentTracker);
	// 	DocumentManager->Initialize(ThisPtr);
	//
	// 	CreateInternalWidgets();
	// 	
	// 	// Register the document factories
	// 	{
	// 		// FCustomAssetSummoner* CustomAssetSummoner = new FCustomAssetSummoner(ThisPtr);
	// 		// TSharedPtr<FDocumentTabFactory> GraphEditorFactory = MakeShareable(CustomAssetSummoner);
	// 		
	// 		// Also store off a reference to the grapheditor factory so we can find all the tabs spawned by it later.
	// 		// GraphEditorTabFactoryPtr = GraphEditorFactory;
	// 		// DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
	// 	}
	// }

	AddApplicationMode(CustomAssetMode, MakeShareable(new FCustomAssetEditorApplicationMode(SharedThis(this))));
	AddApplicationMode(CustomAssetTestMode, MakeShareable(new FCustomAssetTestApplicationMode(SharedThis(this))));

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		CustomAssetEditor::AppIdentifier,
		FTabManager::FLayout::NullLayout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InCustomAsset
	);

	SetCurrentMode(CustomAssetMode);

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
	// WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CustomAssetEditor", "Custom Asset Editor"));
	// const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	// InTabManager->RegisterTabSpawner(TextAssetEditor::TabId, FOnSpawnTab::CreateSP(this, &FCustomAssetEditorToolkit::HandleTabManagerSpawnTab, TextAssetEditor::TabId))
	// 	.SetDisplayName(LOCTEXT("CustomEditorTabName", "Custom Editor"))
	// 	.SetGroup(WorkspaceMenuCategoryRef)
	// 	.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}


void FCustomAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(CustomAssetEditor::TabId);
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
{
}


void FCustomAssetEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}


/* FTextAssetEditorToolkit callbacks
 *****************************************************************************/

TSharedRef<SDockTab> FCustomAssetEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == CustomAssetEditor::TabId)
	{
		TabWidget = SNew(SCustomAssetEditor, CustomAsset, Style);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}

void FCustomAssetEditorToolkit::CreateInternalWidgets()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false);
	// DetailsViewArgs.NotifyHook = this;
	DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(CustomAsset);
	// DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateSP(this, &FTestEditor::IsPropertyEditable));
	// DetailsView->OnFinishedChangingProperties().AddSP(this, &FCustomAssetEditorToolkit::OnFinishedChangingProperties);
}

TSharedRef<SWidget> FCustomAssetEditorToolkit::SpawnProperties()
{
	return
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .FillHeight(1.0f)
		  .HAlign(HAlign_Fill)
		[
			DetailsView.ToSharedRef()
			// SNew(SButton)
		];
}

TSharedRef<SWidget> FCustomAssetEditorToolkit::SpawnEditable()
{
	return
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SCustomAssetEditor, CustomAsset, Style)
		];
}

void FCustomAssetEditorToolkit::RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

FText FCustomAssetEditorToolkit::GetLocalizedMode(FName InMode)
{
	static TMap<FName, FText> LocModes;

	if (LocModes.Num() == 0)
	{
		LocModes.Add(CustomAssetMode, LOCTEXT("CustomAssetMode", "Custom Asset"));
		LocModes.Add(CustomAssetTestMode, LOCTEXT("CustomAssetTestMode", "Custom Asset Test"));
	}

	check(InMode != NAME_None);
	const FText* OutDesc = LocModes.Find(InMode);
	check(OutDesc);
	return *OutDesc;
}


#undef LOCTEXT_NAMESPACE
