// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCExample.h"
#include "GCExampleStyle.h"
#include "GCExampleCommands.h"
#include "LevelEditor.h"
#include "SGCWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName GCExampleTabName("GCExample");

#define LOCTEXT_NAMESPACE "FGCExampleModule"

void FGCExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGCExampleStyle::Initialize();
	FGCExampleStyle::ReloadTextures();

	FGCExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGCExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FGCExampleModule::PluginButtonClicked),
		FCanExecuteAction());
	PluginCommands->MapAction(
		FGCExampleCommands::Get().Command1,
		FExecuteAction::CreateRaw(this, &FGCExampleModule::Command1Handle),
		FCanExecuteAction());
	PluginCommands->MapAction(
		FGCExampleCommands::Get().Command2,
		FExecuteAction::CreateRaw(this, &FGCExampleModule::Command2Handle),
		FCanExecuteAction());
	PluginCommands->MapAction(
		FGCExampleCommands::Get().Command3,
		FExecuteAction::CreateRaw(this, &FGCExampleModule::Command3Handle),
		FCanExecuteAction());
	PluginCommands->MapAction(
		FGCExampleCommands::Get().Command4,
		FExecuteAction::CreateRaw(this, &FGCExampleModule::Command4Handle),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGCExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GCExampleTabName	, FOnSpawnTab::CreateRaw(this, &FGCExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FGCExampleTabTitle", "GCExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FGCExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGCExampleStyle::Shutdown();

	FGCExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GCExampleTabName);
}

void FGCExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(GCExampleTabName);
}

TSharedRef<SDockTab> FGCExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FGCExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("GCExample.cpp"))
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
			SNew(SGCWidget)
		];
}

void FGCExampleModule::Command1Handle()
{
	UE_LOG(LogTemp, Log, TEXT("FGCExampleModule::Command1Handle"));
}

void FGCExampleModule::Command2Handle()
{
	UE_LOG(LogTemp, Log, TEXT("FGCExampleModule::Command2Handle"));
}

void FGCExampleModule::Command3Handle()
{
	UE_LOG(LogTemp, Log, TEXT("FGCExampleModule::Command3Handle"));
}

void FGCExampleModule::Command4Handle()
{
	UE_LOG(LogTemp, Log, TEXT("FGCExampleModule::Command4Handle"));
}

void FGCExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGCExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGCExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGCExampleModule, GCExample)