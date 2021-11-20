// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailViewExampleCommands.h"

#define LOCTEXT_NAMESPACE "FDetailViewExampleModule"

void FDetailViewExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DetailViewExample", "Bring up DetailViewExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
