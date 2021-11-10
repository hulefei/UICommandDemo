// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCExampleCommands.h"

#define LOCTEXT_NAMESPACE "FGCExampleModule"

void FGCExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GCExample", "Bring up GCExample window", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command1, "Action1", "Action1", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command2, "Action2", "Action2", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command3, "Action3", "Action3", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command4, "Action4", "Action4", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
