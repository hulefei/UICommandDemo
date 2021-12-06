// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SerializationObjectStyle.h"

class FSerializationObjectCommands : public TCommands<FSerializationObjectCommands>
{
public:

	FSerializationObjectCommands()
		: TCommands<FSerializationObjectCommands>(TEXT("SerializationObject"), NSLOCTEXT("Contexts", "SerializationObject", "SerializationObject Plugin"), NAME_None, FSerializationObjectStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
