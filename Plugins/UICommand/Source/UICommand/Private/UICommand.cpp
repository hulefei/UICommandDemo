// Copyright Epic Games, Inc. All Rights Reserved.

#include "UICommand.h"

#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "FTestCommands.h"
#include "LevelEditor.h"
#include "TestStyle.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FUICommandModule"


class UTickTimeline;

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
	PluginCommandList->MapAction(
		FTestCommands::Get().CommandB,
		FExecuteAction::CreateRaw(this, &FUICommandModule::CommandAAction),
		FCanExecuteAction());

	//获得关卡编辑器模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//扩展关卡编辑器的菜单
	{
		const TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout"
		                               , EExtensionHook::After
		                               , PluginCommandList
		                               , FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder)
		                               {
			                               Builder.AddMenuEntry(FTestCommands::Get().CommandA);
		                               }));
		MenuExtender->AddMenuExtension("WindowLayout"
		                               , EExtensionHook::After
		                               , PluginCommandList
		                               , FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder)
		                               {
			                               Builder.AddMenuEntry(FTestCommands::Get().CommandB);
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
		// ToolbarExtender->AddToolBarExtension("Settings"
		//                                      , EExtensionHook::After
		//                                      , PluginCommandList
		//                                      , FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
		//                                      {
		// 	                                     Builder.AddToolBarButton(FTestCommands::Get().CommandB);
		//                                      }));
		
		//添加到工具栏方法1
		// LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	//获得内容浏览器模块
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(
		TEXT("ContentBrowser"));
	//增加内容浏览器中Asset右键菜单
	TArray<FContentBrowserMenuExtender_SelectedAssets>& CBAssetMenuExtenderDelegates = ContentBrowserModule.
		GetAllAssetViewContextMenuExtenders();
	CBAssetMenuExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedAssets::CreateLambda(
		[](const TArray<FAssetData>& SelectedAssets)
		{
			TSharedRef<FExtender> Extender(new FExtender());
			Extender->AddMenuExtension(
				"AssetContextReferences",
				EExtensionHook::After,
				nullptr,
				FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
				{
					MenuBuilder.AddMenuEntry(FTestCommands::Get().CommandB);
				}));

			return Extender;
		}));

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
	// TickTimeline = NewObject<UTickTimeline>();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUICommandModule, UICommand)
