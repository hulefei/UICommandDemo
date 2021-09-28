// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EdGraphUtilities.h"
#include "SGraphNode.h"
#include "KismetPins/SGraphPinExec.h"
#include "UObject/Object.h"
#include "CustomAssetGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMASSETEDITOR_API UCustomAssetGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	// virtual TSharedPtr<SGraphNode> CreateVisualWidget() override { return MakeShareable(SGraphNodePtr); }
	//~ End UEdGraphNode Interface

	static UCustomAssetGraphNode* CreateGraphNode(class UEdGraph* ParentGraph, const FVector2D Location);

	SGraphNode* SGraphNodePtr;
};

class SCustomAssetGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SCustomAssetGraphNode){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UCustomAssetGraphNode* InNode);

protected:
	// SGraphNode interface
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	// End of SGraphNode interface
};

// Custom node factory
class FCustomAssetGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UCustomAssetGraphNode* CustomAssetGraphNode = Cast<UCustomAssetGraphNode>(Node))
		{
			return SNew(SCustomAssetGraphNode, CustomAssetGraphNode);
		}

		return nullptr;
	}
};

// Custom pin factory
class FCustomAssetGraphPinFactory : public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override
	{
		UEdGraphNode* Node = Pin->GetOwningNode();
		if(Node && Node->IsA<UCustomAssetGraphNode>())
		{
			return SNew(SGraphPinExec, Pin);
		}
		return nullptr;
	}
};
