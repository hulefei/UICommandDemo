// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WorkflowOrientedApp/WorkflowTabFactory.h"


class FCustomAssetEditorToolkit;
/**
 * 
 */
struct FCustomAssetSummoner : public FWorkflowTabFactory
{
public:
	FCustomAssetSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr);
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<class FCustomAssetEditorToolkit> CustomAssetEditorToolkitPtr;
};
