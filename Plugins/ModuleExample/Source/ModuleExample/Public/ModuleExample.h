// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "ModuleAsset.h"
#include "Modules/ModuleManager.h"

class FModuleExampleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// UModuleAsset* GetModuleAsset() const {return ModuleAsset;}
	
private:
	// UModuleAsset* ModuleAsset = nullptr;
};
