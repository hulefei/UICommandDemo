// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModuleExample.h"

#define LOCTEXT_NAMESPACE "FModuleExampleModule"

void FModuleExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// ModuleAsset = NewObject<UModuleAsset>();
	// ModuleAsset->Name = FString(TEXT("lefeihu"));
	//
	UE_LOG(LogTemp, Log, TEXT("FModuleExampleModule::StartupModule"));
}

void FModuleExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModuleExampleModule, ModuleExample)