// Copyright Epic Games, Inc. All Rights Reserved.

#include "SerializationObject.h"
#include "SerializationObjectStyle.h"
#include "SerializationObjectCommands.h"
#include "SerializationObjectMain.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName SerializationObjectTabName("SerializationObject");

#define LOCTEXT_NAMESPACE "FSerializationObjectModule"

void FSerializationObjectModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSerializationObjectStyle::Initialize();
	FSerializationObjectStyle::ReloadTextures();

	FSerializationObjectCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSerializationObjectCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSerializationObjectModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSerializationObjectModule::RegisterMenus));
}

void FSerializationObjectModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSerializationObjectStyle::Shutdown();

	FSerializationObjectCommands::Unregister();
}

void FSerializationObjectModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	// FText DialogText = FText::Format(
	// 						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	// 						FText::FromString(TEXT("FSerializationObjectModule::PluginButtonClicked()")),
	// 						FText::FromString(TEXT("SerializationObject.cpp"))
	// 				   );
	// FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	USerializationObjectMain::Main();
	// USerializationObjectMain::CreateTextureAsset(TEXT("Texture"), 128, 128);
}

void FSerializationObjectModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSerializationObjectCommands::Get().PluginAction, PluginCommands);
		}
	}

	/* Add to Toolbar */
	// {
	// 	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	// 	{
	// 		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
	// 		{
	// 			FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSerializationObjectCommands::Get().PluginAction));
	// 			Entry.SetCommandList(PluginCommands);
	// 		}
	// 	}
	// }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSerializationObjectModule, SerializationObject)