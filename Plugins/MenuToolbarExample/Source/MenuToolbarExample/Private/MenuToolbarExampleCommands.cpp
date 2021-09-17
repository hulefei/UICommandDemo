// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuToolbarExampleCommands.h"

#define LOCTEXT_NAMESPACE "FMenuToolbarExampleModule"

void FMenuToolbarExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MenuToolbarExample", "Bring up MenuToolbarExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
