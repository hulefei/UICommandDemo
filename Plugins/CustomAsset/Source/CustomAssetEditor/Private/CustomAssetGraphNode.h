// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	//~ End UEdGraphNode Interface

	static UEdGraphNode* CreateGraphNode(class UEdGraph* ParentGraph, const FVector2D Location);
};
