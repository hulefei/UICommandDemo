// Copyright Epic Games, Inc. All Rights Reserved.

#include "UICommand.h"

#include "FTestCommands.h"
#include "LevelEditor.h"
#include "TestStyle.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FUICommandModule"

void FUICommandModule::StartupModule()
{
	FTestCommands::Register();

	//创建UICommandList
	PluginCommandList = MakeShareable(new FUICommandList);
	//为命令映射操作
	PluginCommandList->MapAction(
		FTestCommands::Get().CommandA,
		FExecuteAction::CreateRaw(this, &FUICommandModule::CommandAAction),
		FCanExecuteAction());

	//获得关卡编辑器模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//扩展关卡编辑器的菜单
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout"
			, EExtensionHook::After
			, PluginCommandList
			, FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder)
				{
					Builder.AddMenuEntry(FTestCommands::Get().CommandA);
				}));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	//扩展关卡编辑器的工具栏
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings"
			, EExtensionHook::After
			, PluginCommandList
			, FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
				{
					Builder.AddToolBarButton(FTestCommands::Get().CommandA);
				}));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FTestStyle::Initialize();
	FTestStyle::ReloadTextures();
}

void FUICommandModule::ShutdownModule()
{
	FTestCommands::Unregister();
}

void FUICommandModule::CommandAAction()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Execute CommandA"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUICommandModule, UICommand)