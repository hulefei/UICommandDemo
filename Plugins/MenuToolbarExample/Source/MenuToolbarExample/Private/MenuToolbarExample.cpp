// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuToolbarExample.h"
#include "MenuToolbarExampleStyle.h"
#include "MenuToolbarExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName MenuToolbarExampleTabName("MenuToolbarExample");

#define LOCTEXT_NAMESPACE "FMenuToolbarExampleModule"

void FMenuToolbarExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMenuToolbarExampleStyle::Initialize();
	FMenuToolbarExampleStyle::ReloadTextures();

	FMenuToolbarExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMenuToolbarExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMenuToolbarExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMenuToolbarExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MenuToolbarExampleTabName, FOnSpawnTab::CreateRaw(this, &FMenuToolbarExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMenuToolbarExampleTabTitle", "MenuToolbarExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMenuToolbarExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMenuToolbarExampleStyle::Shutdown();

	FMenuToolbarExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MenuToolbarExampleTabName);
}

TSharedRef<SDockTab> FMenuToolbarExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMenuToolbarExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MenuToolbarExample.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FMenuToolbarExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MenuToolbarExampleTabName);
}

void FMenuToolbarExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMenuToolbarExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMenuToolbarExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMenuToolbarExampleModule, MenuToolbarExample)