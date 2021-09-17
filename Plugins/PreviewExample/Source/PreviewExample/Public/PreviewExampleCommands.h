// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PreviewExampleStyle.h"

class FPreviewExampleCommands : public TCommands<FPreviewExampleCommands>
{
public:

	FPreviewExampleCommands()
		: TCommands<FPreviewExampleCommands>(TEXT("PreviewExample"), NSLOCTEXT("Contexts", "PreviewExample", "PreviewExample Plugin"), NAME_None, FPreviewExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};