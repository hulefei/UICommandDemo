// Copyright Epic Games, Inc. All Rights Reserved.

#include "PreviewExampleCommands.h"

#define LOCTEXT_NAMESPACE "FPreviewExampleModule"

void FPreviewExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "PreviewExample", "Bring up PreviewExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
