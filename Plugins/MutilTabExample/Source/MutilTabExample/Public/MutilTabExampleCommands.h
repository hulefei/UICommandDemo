// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MutilTabExampleStyle.h"

class FMutilTabExampleCommands : public TCommands<FMutilTabExampleCommands>
{
public:

	FMutilTabExampleCommands()
		: TCommands<FMutilTabExampleCommands>(TEXT("MutilTabExample"), NSLOCTEXT("Contexts", "MutilTabExample", "MutilTabExample Plugin"), NAME_None, FMutilTabExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};