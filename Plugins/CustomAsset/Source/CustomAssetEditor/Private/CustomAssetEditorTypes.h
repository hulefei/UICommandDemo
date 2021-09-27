// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomAssetEditorTypes.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMASSETEDITOR_API UCustomAssetEditorTypes : public UObject
{
	GENERATED_UCLASS_BODY()
	static const FName PinCategory_MultipleNodes;
	static const FName PinCategory_SingleComposite;
	static const FName PinCategory_SingleTask;
	static const FName PinCategory_SingleNode;
};
