// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolbarExample.h"
#include "ToolbarExampleEdMode.h"

#define LOCTEXT_NAMESPACE "FToolbarExampleModule"

void FToolbarExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FToolbarExampleEdMode>(FToolbarExampleEdMode::EM_ToolbarExampleEdModeId, LOCTEXT("ToolbarExampleEdModeName", "ToolbarExampleEdMode"), FSlateIcon(), true);
}

void FToolbarExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FToolbarExampleEdMode::EM_ToolbarExampleEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToolbarExampleModule, ToolbarExample)