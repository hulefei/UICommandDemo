// Copyright Epic Games, Inc. All Rights Reserved.

#include "MutilTabExample.h"
#include "MutilTabExampleStyle.h"
#include "MutilTabExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName MutilTabExampleTabName("MutilTabExample");

static const FName TestLayoutWindowTabName("TestLayoutWindow");
static const FName InnerTabName("InnerTab");
static const FName InnerTabName2("InnerTab2");

#define LOCTEXT_NAMESPACE "FMutilTabExampleModule"

void FMutilTabExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FMutilTabExampleStyle::Initialize();
	FMutilTabExampleStyle::ReloadTextures();

	FMutilTabExampleCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMutilTabExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMutilTabExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMutilTabExampleModule::RegisterMenus));

	//注册一个构件Tab的方法OnSpawnPluginTab 并与名字 MutilTabExampleTabName 绑定
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MutilTabExampleTabName,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FMutilTabExampleModule::OnSpawnPluginTab))
	                        .SetDisplayName(LOCTEXT("FMutilTabExampleTabTitle", "MutilTabExample"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);

	{
		//*******Core*****
		//add tab
		//InnerTab的内容：
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(InnerTabName, FOnSpawnTab::CreateLambda(
															[](const FSpawnTabArgs& SpawnTabArgs)
															{
																return
																	SNew(SDockTab)
																	.TabRole(ETabRole::NomadTab)
																	[
																		SNew(STextBlock)
																		.Text(FText::FromString("InnerTab"))
																	];
															}))
								.SetDisplayName(LOCTEXT("InnerTab", "InnerTab"))
								.SetMenuType(ETabSpawnerMenuType::Hidden);

		//InnerTab2的内容：
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(InnerTabName2, FOnSpawnTab::CreateLambda(
															[](const FSpawnTabArgs& SpawnTabArgs)
															{
																return
																	SNew(SDockTab)
																	.TabRole(ETabRole::NomadTab)
																	[
																		SNew(STextBlock)
																		.Text(FText::FromString("InnerTab2"))
																	];
															}))
								.SetDisplayName(LOCTEXT("InnerTab2", "InnerTab2"))
								.SetMenuType(ETabSpawnerMenuType::Hidden);

		//*******Core*****
	}
}

void FMutilTabExampleModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FMutilTabExampleStyle::Shutdown();
	FMutilTabExampleCommands::Unregister();
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MutilTabExampleTabName);
}

TSharedRef<SDockTab> FMutilTabExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//原来的分页：
	const TSharedRef<SDockTab> NomadTab = SNew(SDockTab).TabRole(ETabRole::NomadTab);
	//创建TabManager
	if (!TabManager.IsValid())
	{
		TabManager = FGlobalTabmanager::Get()->NewTabManager(NomadTab);
	}

	//创建布局：
	if (!TabManagerLayout.IsValid())
	{
		TabManagerLayout = FTabManager::NewLayout("TestLayoutWindow")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab(InnerTabName, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab(InnerTabName2, ETabState::OpenedTab)
				)
			);
	}

	//从布局中恢复得到控件
	TSharedRef<SWidget> TabContents = TabManager->RestoreFrom(TabManagerLayout.ToSharedRef(), TSharedPtr<SWindow>()).
	                                              ToSharedRef();

	//设置内容控件
	NomadTab->SetContent(TabContents);

	return NomadTab;
}


void FMutilTabExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MutilTabExampleTabName);
}

void FMutilTabExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMutilTabExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	// {
	// 	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	// 	{
	// 		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
	// 		{
	// 			FToolMenuEntry& Entry = Section.AddEntry(
	// 				FToolMenuEntry::InitToolBarButton(FMutilTabExampleCommands::Get().OpenPluginWindow));
	// 			Entry.SetCommandList(PluginCommands);
	// 		}
	// 	}
	// }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMutilTabExampleModule, MutilTabExample)
