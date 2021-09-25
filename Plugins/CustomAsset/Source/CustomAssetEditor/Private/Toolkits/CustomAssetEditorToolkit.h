// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CustomAsset.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"


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
	FCustomAssetEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);

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
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager);
	TSharedRef<SWidget> SpawnProperties();
	TSharedRef<SWidget> SpawnEditable();
	static FText GetLocalizedMode(FName InMode);
	TSharedPtr<FCustomAssetEditorToolbar> ToolbarBuilder;

	void CreateNewNode() const;
	bool CanCreateNewNode() const;
	void CreateInternalWidgets();
private:
	/** Callback for spawning the Properties tab. */
	TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);
	// void BindCommonCommands() const;
	
private:
	/** The text asset being edited. */
	UCustomAsset* CustomAsset = nullptr;

	/** Pointer to the style set to use for toolkits. */
	TSharedRef<ISlateStyle> Style;

	TSharedPtr<class FDocumentTracker> DocumentManager;
	TSharedPtr<class IDetailsView> DetailsView;

public:
	/** Modes in mode switcher */
	static const FName CustomAssetMode;
	static const FName CustomAssetTestMode;
};
