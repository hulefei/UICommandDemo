// Copyright Epic Games, Inc. All Rights Reserved.

#include "MutilTabExampleCommands.h"

#define LOCTEXT_NAMESPACE "FMutilTabExampleModule"

void FMutilTabExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MutilTabExample", "Bring up MutilTabExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
