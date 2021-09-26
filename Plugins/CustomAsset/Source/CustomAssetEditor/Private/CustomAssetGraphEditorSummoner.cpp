// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetGraphEditorSummoner.h"

#include "CustomAssetEditorTabs.h"
#include "Toolkits/CustomAssetEditorToolkit.h"

FCustomAssetGraphEditorSummoner::FCustomAssetGraphEditorSummoner(
	TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr,
	FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback)
	: FDocumentTabFactoryForObjects<UEdGraph>(FCustomAssetEditorTabs::GraphEditorID, InCustomAssetEditorPtr)
	  , CustomAssetEditorPtr(InCustomAssetEditorPtr)
	  , OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
}

void FCustomAssetGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(CustomAssetEditorPtr.IsValid());
	const TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	CustomAssetEditorPtr.Pin()->OnGraphEditorFocused(GraphEditor);
}

void FCustomAssetGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	GraphEditor->NotifyGraphChanged();
}

TAttribute<FText> FCustomAssetGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* DocumentID) const
{
	return TAttribute<FText>( FText::FromString( DocumentID->GetName() ) );
}

TSharedRef<SWidget> FCustomAssetGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info,
                                                                            UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FCustomAssetGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return FEditorStyle::GetBrush("NoBrush");
}

void FCustomAssetGraphEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
{
	check(CustomAssetEditorPtr.IsValid());
	check(CustomAssetEditorPtr.Pin()->GetCustomAsset());

	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());

	FVector2D ViewLocation;
	float ZoomAmount;
	GraphEditor->GetViewLocation(ViewLocation, ZoomAmount);

	UEdGraph* Graph = FTabPayload_UObject::CastChecked<UEdGraph>(Payload);
	CustomAssetEditorPtr.Pin()->GetCustomAsset()->LastEditedDocuments.Add(FEditedDocumentInfo(Graph, ViewLocation, ZoomAmount));
}
