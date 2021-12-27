// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PreStudyExampleStyle.h"

class FPreStudyExampleCommands : public TCommands<FPreStudyExampleCommands>
{
public:

	FPreStudyExampleCommands()
		: TCommands<FPreStudyExampleCommands>(TEXT("PreStudyExample"), NSLOCTEXT("Contexts", "PreStudyExample", "PreStudyExample Plugin"), NAME_None, FPreStudyExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};