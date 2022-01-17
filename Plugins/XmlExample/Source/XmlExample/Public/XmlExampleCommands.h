// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "XmlExampleStyle.h"

class FXmlExampleCommands : public TCommands<FXmlExampleCommands>
{
public:

	FXmlExampleCommands()
		: TCommands<FXmlExampleCommands>(TEXT("XmlExample"), NSLOCTEXT("Contexts", "XmlExample", "XmlExample Plugin"), NAME_None, FXmlExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
