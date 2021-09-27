// Fill out your copyright notice in the Description page of Project Settings.


#include "UEdGraphSchema_CustomAsset.h"

#include "GraphEditorActions.h"
#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Framework/Commands/GenericCommands.h"

#define LOCTEXT_NAMESPACE "UEdGraphSchema_CustomAsset"

UEdGraphSchema_CustomAsset::UEdGraphSchema_CustomAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEdGraphSchema_CustomAsset::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
}

void UEdGraphSchema_CustomAsset::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
}

void UEdGraphSchema_CustomAsset::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("CustomAssetGraphSchemaNodeActions", LOCTEXT("ClassActionsMenuHeader", "Node Actions"));
		{
			Section.AddMenuEntry(FGenericCommands::Get().Delete);
			Section.AddMenuEntry(FGenericCommands::Get().Cut);
			Section.AddMenuEntry(FGenericCommands::Get().Copy);
			Section.AddMenuEntry(FGenericCommands::Get().Duplicate);
			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
		}
	}
	Super::GetContextMenuActions(Menu,  Context);
}

const FPinConnectionResponse UEdGraphSchema_CustomAsset::CanCreateConnection(const UEdGraphPin* A,
	const UEdGraphPin* B) const
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode", "Both are on the same node"));
	}
	// Make sure the pins are not on the same node
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
}

const FPinConnectionResponse UEdGraphSchema_CustomAsset::CanMergeNodes(const UEdGraphNode* A,
	const UEdGraphNode* B) const
{
	FPinConnectionResponse Response;
	return Response;
}

FLinearColor UEdGraphSchema_CustomAsset::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	FLinearColor Color;
	return Color;
}

FConnectionDrawingPolicy* UEdGraphSchema_CustomAsset::CreateConnectionDrawingPolicy(int32 InBackLayerID,
	int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements,
	UEdGraph* InGraphObj) const
{
	return nullptr;
}

bool UEdGraphSchema_CustomAsset::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return false;
}

int32 UEdGraphSchema_CustomAsset::GetCurrentVisualizationCacheID() const
{
	return 0;
}

void UEdGraphSchema_CustomAsset::ForceVisualizationCacheClear() const
{
}

bool UEdGraphSchema_CustomAsset::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	return Super::TryCreateConnection(A, B);
}

#undef LOCTEXT_NAMESPACE
