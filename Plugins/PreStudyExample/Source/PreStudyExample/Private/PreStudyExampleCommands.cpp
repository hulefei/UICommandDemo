// Copyright Epic Games, Inc. All Rights Reserved.

#include "PreStudyExampleCommands.h"

#define LOCTEXT_NAMESPACE "FPreStudyExampleModule"

void FPreStudyExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "PreStudyExample", "Bring up PreStudyExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
