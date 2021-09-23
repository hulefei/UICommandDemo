// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Toolkits/CustomAssetEditorToolkit.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/**
 * 
 */
class FCustomAssetTestApplicationMode : public FApplicationMode
{
public:
	FCustomAssetTestApplicationMode(TSharedPtr<FCustomAssetEditorToolkit> InCustomAssetEditor);
	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:
	TWeakPtr<FCustomAssetEditorToolkit> CustomAssetEditor;

	// Set of spawnable tabs in behavior tree editing mode
	FWorkflowAllowedTabSet CustomAssetEditorTabFactories;
};
