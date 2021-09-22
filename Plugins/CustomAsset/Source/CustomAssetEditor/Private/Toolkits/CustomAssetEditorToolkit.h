// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CustomAsset.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API FCustomAssetEditorToolkit
	: public FAssetEditorToolkit
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

	private:

	/** Callback for spawning the Properties tab. */
	TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);

	private:

	/** The text asset being edited. */
	UCustomAsset* CustomAsset = nullptr;

	/** Pointer to the style set to use for toolkits. */
	TSharedRef<ISlateStyle> Style;
};
