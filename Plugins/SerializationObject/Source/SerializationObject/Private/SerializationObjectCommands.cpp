// Copyright Epic Games, Inc. All Rights Reserved.

#include "SerializationObjectCommands.h"

#define LOCTEXT_NAMESPACE "FSerializationObjectModule"

void FSerializationObjectCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "SerializationObject", "Execute SerializationObject action",
	           EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
