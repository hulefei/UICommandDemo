// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailViewExample.h"

#include "CustomDetailStructViewCustomization.h"
#include "DetailViewExampleStyle.h"
#include "DetailViewExampleCommands.h"
#include "LevelEditor.h"
#include "SDetailViewWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "PropertyEditor/Private/SDetailsView.h"

static const FName DetailViewExampleTabName("DetailViewExample");

#define LOCTEXT_NAMESPACE "FDetailViewExampleModule"

void FDetailViewExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDetailViewExampleStyle::Initialize();
	FDetailViewExampleStyle::ReloadTextures();

	FDetailViewExampleCommands::Register();

	// Register the details customizer
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("CustomDetailStruct", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCustomDetailStructViewCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDetailViewExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDetailViewExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDetailViewExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DetailViewExampleTabName, FOnSpawnTab::CreateRaw(this, &FDetailViewExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDetailViewExampleTabTitle", "DetailViewExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDetailViewExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("CustomDetailStruct");

	FDetailViewExampleStyle::Shutdown();

	FDetailViewExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DetailViewExampleTabName);
}

TSharedRef<SDockTab> FDetailViewExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDetailViewExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("DetailViewExample.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SDetailViewWidget)
		];
}

void FDetailViewExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DetailViewExampleTabName);
}

void FDetailViewExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDetailViewExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDetailViewExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDetailViewExampleModule, DetailViewExample)