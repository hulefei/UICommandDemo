// Copyright Epic Games, Inc. All Rights Reserved.

#include "TickExample.h"

#include "TickTimeline.h"
#include "TickTimelineObject.h"

#define LOCTEXT_NAMESPACE "FTickExampleModule"

void FTickExampleModule::StartupModule()
{
	// TickTimelineObject = NewObject<UTickTimelineObject>();
	// TickTimelineObject->Start();
	// TickTimeline = NewObject<UTickTimeline>();
}

void FTickExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTickExampleModule, TickExample)