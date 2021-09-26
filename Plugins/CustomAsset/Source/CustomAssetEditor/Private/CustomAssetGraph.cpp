// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetGraph.h"

#include "UEdGraphSchema_CustomAsset.h"

UCustomAssetGraph::UCustomAssetGraph(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Schema = UEdGraphSchema_CustomAsset::StaticClass();
}
