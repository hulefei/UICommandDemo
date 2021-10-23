// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCExampleCommands.h"

#define LOCTEXT_NAMESPACE "FGCExampleModule"

void FGCExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GCExample", "Bring up GCExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
