// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUICommandModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//CommandA所对应的操作
	void CommandAAction();

	TSharedPtr<class FUICommandList> PluginCommandList;

private:
	// class UTickTimeline* TickTimeline = nullptr;
	// FDelegateHandle MyTickerHandle;
};
