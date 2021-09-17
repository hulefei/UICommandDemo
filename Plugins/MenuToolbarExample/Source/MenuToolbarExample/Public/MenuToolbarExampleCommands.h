// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MenuToolbarExampleStyle.h"

class FMenuToolbarExampleCommands : public TCommands<FMenuToolbarExampleCommands>
{
public:

	FMenuToolbarExampleCommands()
		: TCommands<FMenuToolbarExampleCommands>(TEXT("MenuToolbarExample"), NSLOCTEXT("Contexts", "MenuToolbarExample", "MenuToolbarExample Plugin"), NAME_None, FMenuToolbarExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};