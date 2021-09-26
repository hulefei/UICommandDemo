// Fill out your copyright notice in the Description page of Project Settings.


#include "UEdGraphSchema_CustomAsset.h"

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
}

const FPinConnectionResponse UEdGraphSchema_CustomAsset::CanCreateConnection(const UEdGraphPin* A,
	const UEdGraphPin* B) const
{
	FPinConnectionResponse Response;
	return Response;
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
