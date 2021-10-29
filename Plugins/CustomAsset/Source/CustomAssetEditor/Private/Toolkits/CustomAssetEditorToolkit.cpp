// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
// #include "EditorStyleSet.h"
#include "Widgets/SCustomAssetEditor.h"
#include "CustomAsset.h"
// #include "CustomAssetCommands.h"
#include "CustomAssetEditorApplicationMode.h"
#include "CustomAssetEditorToolbar.h"
#include "CustomAssetTestApplicationMode.h"
// #include "CustomAssetSummoner.h"
#include "BlueprintEditor.h"
#include "CustomAssetGraph.h"
#include "CustomAssetGraphEditorSummoner.h"
#include "CustomAssetGraphNode.h"
#include "UEdGraphSchema_CustomAsset.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"
#include "Timeline/SCustomAssetTimeline.h"
#include "KTimeline/SCustomAssetKTimeline.h"

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

FCustomAssetEditorToolkit::FCustomAssetEditorToolkit()
	: CustomAsset(nullptr)
{
}


FCustomAssetEditorToolkit::~FCustomAssetEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	// FCustomAssetCommands::Unregister();

	GEditor->UnregisterForUndo(this);
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

	CustomAssetCommandList = MakeShareable(new FUICommandList);
	CustomAssetCommandList->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateSP(this, &FCustomAssetEditorToolkit::DeleteSelectedWidgets),
		FCanExecuteAction::CreateSP(this, &FCustomAssetEditorToolkit::CanDeleteSelectedWidgets)
		);

	const TSharedPtr<FCustomAssetEditorToolkit> ThisPtr(SharedThis(this));
	if (!DocumentManager.IsValid())
	{
		DocumentManager = MakeShareable(new FDocumentTracker);
		DocumentManager->Initialize(ThisPtr);

		const TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FCustomAssetGraphEditorSummoner(ThisPtr,
		                                                                                                             FCustomAssetGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(
			                                                                                                             this, &FCustomAssetEditorToolkit::CreateGraphEditorWidget)
		));
		GraphEditorTabFactoryPtr = GraphEditorFactory;
		DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
	}

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

	// FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	DocumentManager->SetTabManager(InTabManager);
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
	
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
		TabWidget = SNew(SCustomAssetEditor, CustomAsset);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}

TSharedRef<SGraphEditor> FCustomAssetEditorToolkit::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);
	// CreateCommandList();
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FCustomAssetEditorToolkit::OnSelectedNodesChanged);
	// InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FTestEditor::OnNodeDoubleClicked);
	// InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FTestEditor::OnNodeTitleCommitted);

	// Make title bar
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
    		.BorderImage(FEditorStyle::GetBrush(TEXT("Graph.TitleBackground")))
    		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Center)
			  .FillWidth(1.f)
			[
				SNew(STextBlock)
    			.Text(LOCTEXT("CustomAssetGraphLabel", "Custom Asset"))
    		.TextStyle(FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
			]
		];

	// Make full graph editor
	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
    		.AdditionalCommands(CustomAssetCommandList)
			.GraphToEdit(InGraph)
    		// .IsEditable(this, &FTestEditor::InEditingMode, bGraphIsEditable)
    		.Appearance(this, &FCustomAssetEditorToolkit::GetGraphAppearance)
    		.TitleBar(TitleBarWidget)
    		.GraphToEdit(InGraph)
    		.GraphEvents(InEvents);
}

bool FCustomAssetEditorToolkit::CanDeleteSelectedWidgets()
{
	return true;
}

void FCustomAssetEditorToolkit::DeleteSelectedWidgets()
{
	UE_LOG(LogTemp, Log, TEXT("DeleteSelectedWidgets"));
	for (auto Node : SelectedWidgets)
	{
		auto SNode = static_cast<UEdGraphNode*>(Node);
		check(SNode);
		SNode->DestroyNode();
	}
}

void FCustomAssetEditorToolkit::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
	SelectedWidgets = NewSelection;
}

FGraphAppearanceInfo FCustomAssetEditorToolkit::GetGraphAppearance() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText", "CUSTOM ASSET");
	return AppearanceInfo;
}

void FCustomAssetEditorToolkit::OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor)
{
	UpdateGraphEdPtr = InGraphEditor;

	FGraphPanelSelectionSet CurrentSelection;
	CurrentSelection = InGraphEditor->GetSelectedNodes();
	OnSelectedNodesChanged(CurrentSelection);
}

void FCustomAssetEditorToolkit::RestoreBehaviorTree()
{
	// Update BT asset data based on saved graph to have correct data in editor
	UCustomAssetGraph* MyGraph = Cast<UCustomAssetGraph>(CustomAsset->CustomAssetGraph);
	const bool bNewGraph = MyGraph == NULL;
	if (MyGraph == NULL)
	{
		CustomAsset->CustomAssetGraph = FBlueprintEditorUtils::CreateNewGraph(CustomAsset, TEXT("Custom Asset"), UCustomAssetGraph::StaticClass(), UEdGraphSchema_CustomAsset::StaticClass());
		MyGraph = Cast<UCustomAssetGraph>(CustomAsset->CustomAssetGraph);

		// Initialize the behavior tree graph
		const UEdGraphSchema* Schema = MyGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*MyGraph);

		// MyGraph->OnCreated();
	}
	else
	{
		// MyGraph->OnLoaded();
	}

	// MyGraph->Initialize();

	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(MyGraph);
	TSharedPtr<SDockTab> DocumentTab = DocumentManager->OpenDocument(Payload, bNewGraph ? FDocumentTracker::OpenNewDocument : FDocumentTracker::RestorePreviousDocument);

	if(CustomAsset->LastEditedDocuments.Num() > 0)
	{
		TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(DocumentTab->GetContent());
		GraphEditor->SetViewLocation(CustomAsset->LastEditedDocuments[0].SavedViewOffset, CustomAsset->LastEditedDocuments[0].SavedZoomAmount);
	}

	// const bool bIncreaseVersionNum = false;
	// if(bNewGraph)
	// {
	// 	MyGraph->UpdateAsset(UBehaviorTreeGraph::ClearDebuggerFlags | UBehaviorTreeGraph::KeepRebuildCounter);
	// 	RefreshBlackboardViewsAssociatedObject();
	// }
	// else
	// {
	// 	MyGraph->UpdateAsset(UBehaviorTreeGraph::KeepRebuildCounter);
	// 	RefreshDebugger();
	// }

	// FAbortDrawHelper EmptyMode;
	// bShowDecoratorRangeLower = false;
	// bShowDecoratorRangeSelf = false;
	// bSelectedNodeIsInjected = false;
	// bSelectedNodeIsRootLevel = false;
	// MyGraph->UpdateAbortHighlight(EmptyMode, EmptyMode);
}

void FCustomAssetEditorToolkit::SaveEditedObjectState() const
{
	// Clear currently edited documents
	CustomAsset->LastEditedDocuments.Empty();

	// Ask all open documents to save their state, which will update LastEditedDocuments
	DocumentManager->SaveAllState();
}

//Custom

// void FCustomAssetEditorToolkit::BindCommonCommands() const
// {
// ToolkitCommands->MapAction(FCustomAssetCommands::Get().Action1,
// 		FExecuteAction::CreateSP(this, &FCustomAssetEditorToolkit::CreateNewNode),
// 		FCanExecuteAction::CreateSP(this, &FCustomAssetEditorToolkit::CanCreateNewNode)
// 		);
// }

void FCustomAssetEditorToolkit::CreateNewNode() const
{
	// const FText DialogText = FText::Format(
	// 	LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	// 	FText::FromString(TEXT("FSimpleEditorsModule::PluginButtonClicked()")),
	// 	FText::FromString(TEXT("SimpleEditors.cpp"))
	// );
	// FMessageDialog::Debugf(DialogText);

	UCustomAssetGraph* MyGraph = Cast<UCustomAssetGraph>(CustomAsset->CustomAssetGraph);
	UCustomAssetGraphNode::CreateGraphNode(MyGraph, FVector2D::ZeroVector);
}

bool FCustomAssetEditorToolkit::CanCreateNewNode() const
{
	return true;
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
			SNew(SCustomAssetEditor, CustomAsset)
		];
}

TSharedRef<SWidget> FCustomAssetEditorToolkit::SpawnTimeline()
{
	return
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			// SNew(SCustomAssetEditor, CustomAsset, Style)
			SNew(SCustomAssetTimeline)
		];
}

TSharedRef<SWidget> FCustomAssetEditorToolkit::SpawnKTimeline()
{
	return
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			// SNew(SCustomAssetEditor, CustomAsset, Style)
			SNew(SCustomAssetKTimeline)
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
