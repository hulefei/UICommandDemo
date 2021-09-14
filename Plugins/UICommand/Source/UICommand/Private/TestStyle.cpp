#include "TestStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FTestStyle::StyleInstance = NULL;

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

void FTestStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTestStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

void FTestStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

FName FTestStyle::GetStyleSetName()
{
	return TEXT("TestStyle");
}

TSharedRef<FSlateStyleSet> FTestStyle::Create()
{
	//创建一个新的Style实例：
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));

	//设置资源目录，为本插件的Resources目录
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("UICommand")->GetBaseDir() / TEXT("Resources"));

	//注册图标：
	// Style->Set("TestCommands.CommandA", new IMAGE_BRUSH(TEXT("Icon128"), Icon128x128));
	Style->Set("TestCommands.CommandA", new IMAGE_BRUSH(TEXT("ButtonIcon_40x"), Icon40x40));

	return Style;
}
