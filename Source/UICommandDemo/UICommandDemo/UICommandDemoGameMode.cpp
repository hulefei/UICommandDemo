// Copyright Epic Games, Inc. All Rights Reserved.

#include "UICommandDemoGameMode.h"
#include "UICommandDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUICommandDemoGameMode::AUICommandDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
