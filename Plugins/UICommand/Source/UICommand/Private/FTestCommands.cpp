// Fill out your copyright notice in the Description page of Project Settings.


#include "FTestCommands.h"

#include "TestStyle.h"

#define LOCTEXT_NAMESPACE "FTestYaksueModule"

FTestCommands::FTestCommands() : TCommands<FTestCommands>(
	TEXT("TestCommands")
	, NSLOCTEXT("Contexts", "TestYaksueCommands", "TestYaksue Plugin")
	, NAME_None
	, FTestStyle::GetStyleSetName())
{
	
}

void FTestCommands::RegisterCommands()
{
	UI_COMMAND(CommandA, "TestCommandA", "Execute TestYaksue CommandA", EUserInterfaceActionType::Button, FInputChord());
}


#undef LOCTEXT_NAMESPACE