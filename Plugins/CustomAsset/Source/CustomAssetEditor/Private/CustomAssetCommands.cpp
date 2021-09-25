// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetCommands.h"

#define LOCTEXT_NAMESPACE "BehaviorTreeEditorCommands"

FCustomAssetCommands::FCustomAssetCommands()
: TCommands<FCustomAssetCommands>("BTEditor.Common", LOCTEXT("Common", "Common"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

void FCustomAssetCommands::RegisterCommands()
{
	UI_COMMAND(Action1, "Action1", "Action1 Description.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F));
}

#undef LOCTEXT_NAMESPACE
