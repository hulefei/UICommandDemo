// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CustomAsset.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"


class FCustomAssetEditorToolbar;

class CUSTOMASSETEDITOR_API FCustomAssetEditorToolkit
	: public FWorkflowCentricApplication//FAssetEditorToolkit // FWorkflowCentricApplication
	  , public FEditorUndoClient
	  , public FGCObject
{
public:
	/**
	* Creates and initializes a new instance.
	*
	* @param InStyle The style set to use.
	*/
	FCustomAssetEditorToolkit();

	/** Virtual destructor. */
	virtual ~FCustomAssetEditorToolkit();

	public:

	/**
	* Initializes the editor tool kit.
	*
	* @param InTextAsset The UTextAsset asset to edit.
	* @param InMode The mode to create the toolkit in.
	* @param InToolkitHost The toolkit host.
	*/
	void Initialize(UCustomAsset* InCustomAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);

	/** Access the toolbar builder for this editor */
	TSharedPtr<FCustomAssetEditorToolbar> GetToolbarBuilder() { return ToolbarBuilder; }
	
	public:

	//~ FAssetEditorToolkit interface

	virtual FString GetDocumentationLink() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	public:

	//~ IToolkit interface

	virtual FText GetBaseToolkitName() const override;
	virtual FName GetToolkitFName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

	public:

	//~ FGCObject interface

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	protected:

	//~ FEditorUndoClient interface

	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

public:
	//~ Custom
	
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager);
	TSharedRef<SWidget> SpawnProperties();
	TSharedRef<SWidget> SpawnEditable();
	TSharedRef<SWidget> SpawnTimeline();
	TSharedRef<SWidget> SpawnKTimeline();
	static FText GetLocalizedMode(FName InMode);

	void CreateNewNode() const;
	bool CanCreateNewNode() const;
	void CreateInternalWidgets();
	void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);
	void RestoreBehaviorTree();
	void SaveEditedObjectState() const;
	
	UCustomAsset* GetCustomAsset() const 
	{
		return CustomAsset; 
	}
	
	TSharedPtr<FCustomAssetEditorToolbar> ToolbarBuilder;
private:
	/** Callback for spawning the Properties tab. */
	TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);
	// void BindCommonCommands() const;
	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
	bool CanDeleteSelectedWidgets();
	void DeleteSelectedWidgets();
	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);
	//定义Graph右下角样式
	FGraphAppearanceInfo GetGraphAppearance() const;
private:
	/** The text asset being edited. */
	UCustomAsset* CustomAsset = nullptr;

	TSharedPtr<class FDocumentTracker> DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;
	TSharedPtr<class IDetailsView> DetailsView;
	/** Command list for handling widget actions in the WidgetBlueprintEditor */
	TSharedPtr< FUICommandList > CustomAssetCommandList;
	/** Currently focused graph */
	TWeakPtr<SGraphEditor> UpdateGraphEdPtr;
	/** The currently selected preview widgets in the preview GUI */
	TSet< UObject* > SelectedWidgets;

public:
	/** Modes in mode switcher */
	static const FName CustomAssetMode;
	static const FName CustomAssetTestMode;
};
