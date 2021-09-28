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

UCustomAssetGraphNode* UCustomAssetGraphNode::CreateGraphNode(class UEdGraph* ParentGraph, const FVector2D Location)
{
	FGraphNodeCreator<UCustomAssetGraphNode> NodeCreator(*ParentGraph);
	UCustomAssetGraphNode* result = NodeCreator.CreateNode();
	NodeCreator.Finalize();
	return result;
	
	// if(ParentGraph == NULL) return NULL;
	// UEdGraphNode* NodeTemplate = NewObject<UCustomAssetGraphNode>(ParentGraph);
	// ParentGraph->Modify();
	// NodeTemplate->SetFlags(RF_Transactional);
	// // set outer to be the graph so it doesn't go away
	// NodeTemplate->Rename(NULL, ParentGraph, REN_NonTransactional);
	// ParentGraph->AddNode(NodeTemplate, true);
	// NodeTemplate->CreateNewGuid();
	// NodeTemplate->NodePosX = Location.X;
	// NodeTemplate->NodePosY = Location.Y;
	// // ResultNode->SnapToGrid(AE_SNAP_GRID);
	// // setup pins after placing node
	// NodeTemplate->AllocateDefaultPins();
	// return NodeTemplate;
}

// ~SCustomAssetGraphNode
void SCustomAssetGraphNode::Construct(const FArguments& InArgs, UCustomAssetGraphNode* InNode)
{
	GraphNode = InNode;
	InNode->SGraphNodePtr = SharedThis(this);
	// InNode->UpdatePins();
	UpdateGraphNode();
}

TSharedRef<SWidget> SCustomAssetGraphNode::CreateNodeContentArea()
{
	// NODE CONTENT AREA
	return SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("NoBorder"))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(0, 3))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			// LEFT
			SAssignNew(LeftNodeBox, SVerticalBox)
		]
		//********自定义的内容
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.FillWidth(1.0f)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush(TEXT("ToolPanel.GroupBorder")))
			[
				SNew(SButton)
				// SAssignNew(ActionListView, SListView<UObject*>)
				// .ItemHeight(30)
				// .SelectionMode(ESelectionMode::None)
				// //.OnSelectionChanged_Raw(this, &FSKBrowser::OnSelectionChanged)
				// .ListItemsSource(&Actions)
				// .OnGenerateRow_Raw(this, &SSegmentGraphNode::ActionList_GenerateRow)
			]
		]
		//**********************
	+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		[
			// RIGHT
			SAssignNew(RightNodeBox, SVerticalBox)
		]
		];
}

#undef LOCTEXT_NAMESPACE
