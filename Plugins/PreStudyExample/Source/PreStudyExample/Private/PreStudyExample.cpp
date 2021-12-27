// Copyright Epic Games, Inc. All Rights Reserved.

#include "PreStudyExample.h"
#include "PreStudyExampleStyle.h"
#include "PreStudyExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SPreStudyWidget.h"

static const FName PreStudyExampleTabName("PreStudyExample");

#define LOCTEXT_NAMESPACE "FPreStudyExampleModule"

void FPreStudyExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPreStudyExampleStyle::Initialize();
	FPreStudyExampleStyle::ReloadTextures();

	FPreStudyExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPreStudyExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPreStudyExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPreStudyExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PreStudyExampleTabName, FOnSpawnTab::CreateRaw(this, &FPreStudyExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPreStudyExampleTabTitle", "PreStudyExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPreStudyExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPreStudyExampleStyle::Shutdown();

	FPreStudyExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PreStudyExampleTabName);
}

TSharedRef<SDockTab> FPreStudyExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPreStudyExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PreStudyExample.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			// SNew(SBox)
			// .HAlign(HAlign_Center)
			// .VAlign(VAlign_Center)
			// [
			// 	SNew(STextBlock)
			// 	.Text(WidgetText)
			// ]
			SNew(SPreStudyWidget)
		];
}

void FPreStudyExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(PreStudyExampleTabName);
}

void FPreStudyExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FPreStudyExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FPreStudyExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPreStudyExampleModule, PreStudyExample)