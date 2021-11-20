// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DetailViewExampleStyle.h"

class FDetailViewExampleCommands : public TCommands<FDetailViewExampleCommands>
{
public:

	FDetailViewExampleCommands()
		: TCommands<FDetailViewExampleCommands>(TEXT("DetailViewExample"), NSLOCTEXT("Contexts", "DetailViewExample", "DetailViewExample Plugin"), NAME_None, FDetailViewExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};