// Copyright Epic Games, Inc. All Rights Reserved.

#include "XmlExample.h"
#include "XmlExampleStyle.h"
#include "XmlExampleCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "XmlMain.h"

static const FName XmlExampleTabName("XmlExample");

#define LOCTEXT_NAMESPACE "FXmlExampleModule"

void FXmlExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FXmlExampleStyle::Initialize();
	FXmlExampleStyle::ReloadTextures();

	FXmlExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FXmlExampleCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FXmlExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FXmlExampleModule::RegisterMenus));
}

void FXmlExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FXmlExampleStyle::Shutdown();

	FXmlExampleCommands::Unregister();
}

void FXmlExampleModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	auto XmlMain = NewObject<UXmlMain>();
	XmlMain->Main();
}

void FXmlExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FXmlExampleCommands::Get().PluginAction, PluginCommands);
		}
	}

	// {
	// 	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	// 	{
	// 		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
	// 		{
	// 			FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FXmlExampleCommands::Get().PluginAction));
	// 			Entry.SetCommandList(PluginCommands);
	// 		}
	// 	}
	// }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXmlExampleModule, XmlExample)