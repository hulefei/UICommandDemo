// Copyright Epic Games, Inc. All Rights Reserved.

#include "PreviewExample.h"
#include "PreviewExampleStyle.h"
#include "PreviewExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"
#include "STestEditorViewport.h"
#include "STestPreview.h"

static const FName PreviewExampleTabName("PreviewExample");

#define LOCTEXT_NAMESPACE "FPreviewExampleModule"

void FPreviewExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPreviewExampleStyle::Initialize();
	FPreviewExampleStyle::ReloadTextures();

	FPreviewExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPreviewExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPreviewExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPreviewExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PreviewExampleTabName, FOnSpawnTab::CreateRaw(this, &FPreviewExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPreviewExampleTabTitle", "PreviewExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPreviewExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPreviewExampleStyle::Shutdown();

	FPreviewExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PreviewExampleTabName);
}

TSharedRef<SDockTab> FPreviewExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPreviewExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PreviewExample.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			//创建预览视窗控件
			// SNew(STestEditorViewport)
			SNew(STestPreview)
		];
}

void FPreviewExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(PreviewExampleTabName);
}

void FPreviewExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FPreviewExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	//添加到工具栏方法2
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FPreviewExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPreviewExampleModule, PreviewExample)