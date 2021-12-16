// Copyright Epic Games, Inc. All Rights Reserved.

#include "UICommandDemo.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "UICommandDemo"

class FUICommandDemoModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		UE_LOG(LogTemp, Log, TEXT("FUICommandDemoModule StartupModuleStartupModule"));
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, UICommandDemo, "UICommandDemo" );

#undef LOCTEXT_NAMESPACE