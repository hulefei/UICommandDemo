// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "Toolkits/CustomAssetEditorToolkit.h"

/**
* 
*/
class CUSTOMASSETEDITOR_API FCustomAssetTimelineSummoner : public FWorkflowTabFactory
{
	public:
	FCustomAssetTimelineSummoner(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditorPtr);

	//FWorkflowTabFactory Implement
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

	protected:
	TWeakPtr<class FCustomAssetEditorToolkit> CustomAssetEditorToolkitPtr;
};
