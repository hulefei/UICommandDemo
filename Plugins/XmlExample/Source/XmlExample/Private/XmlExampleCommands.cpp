// Copyright Epic Games, Inc. All Rights Reserved.

#include "XmlExampleCommands.h"

#define LOCTEXT_NAMESPACE "FXmlExampleModule"

void FXmlExampleCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "XmlExample", "Execute XmlExample action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
