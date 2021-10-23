// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GCExampleStyle.h"

class FGCExampleCommands : public TCommands<FGCExampleCommands>
{
public:

	FGCExampleCommands()
		: TCommands<FGCExampleCommands>(TEXT("GCExample"), NSLOCTEXT("Contexts", "GCExample", "GCExample Plugin"), NAME_None, FGCExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};