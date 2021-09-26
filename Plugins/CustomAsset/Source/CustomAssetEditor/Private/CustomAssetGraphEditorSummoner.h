// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"

struct  FCustomAssetGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>
{
public:
	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);
	FCustomAssetGraphEditorSummoner(TSharedPtr<class FCustomAssetEditorToolkit> InCustomAssetEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);
	virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;
	virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;
protected:
	virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override;
	virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;

	virtual const FSlateBrush*
	GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;
	void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const;
	
	TWeakPtr<class FCustomAssetEditorToolkit> CustomAssetEditorPtr;
	FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;
};
