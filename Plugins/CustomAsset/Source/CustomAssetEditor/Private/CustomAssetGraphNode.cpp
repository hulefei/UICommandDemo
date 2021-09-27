// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetGraphNode.h"

#include "CustomAssetEditorTypes.h"
#include "EdGraph/EdGraphNode.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

UCustomAssetGraphNode::UCustomAssetGraphNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UCustomAssetGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UCustomAssetEditorTypes::PinCategory_MultipleNodes, TEXT("In"));
	CreatePin(EGPD_Output, UCustomAssetEditorTypes::PinCategory_MultipleNodes, TEXT("Out"));
}

FText UCustomAssetGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FText TooltipDesc = LOCTEXT("NodeTitle", "NodeTitle!");
	return TooltipDesc;
}

FText UCustomAssetGraphNode::GetTooltipText() const
{
	FText TooltipDesc = LOCTEXT("Tooltip", "Tooltip!");
	return TooltipDesc;
}

UEdGraphNode* UCustomAssetGraphNode::CreateGraphNode(class UEdGraph* ParentGraph, const FVector2D Location)
{
	if(ParentGraph == NULL) return NULL;
	UEdGraphNode* NodeTemplate = NewObject<UCustomAssetGraphNode>(ParentGraph);
	ParentGraph->Modify();
	NodeTemplate->SetFlags(RF_Transactional);
	// set outer to be the graph so it doesn't go away
	NodeTemplate->Rename(NULL, ParentGraph, REN_NonTransactional);
	ParentGraph->AddNode(NodeTemplate, true);
	NodeTemplate->CreateNewGuid();
	NodeTemplate->NodePosX = Location.X;
	NodeTemplate->NodePosY = Location.Y;
	// ResultNode->SnapToGrid(AE_SNAP_GRID);
	// setup pins after placing node
	NodeTemplate->AllocateDefaultPins();
	return NodeTemplate;
}

#undef LOCTEXT_NAMESPACE
