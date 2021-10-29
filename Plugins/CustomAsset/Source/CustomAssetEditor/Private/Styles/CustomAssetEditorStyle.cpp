#include "CustomAssetEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FCustomAssetEditorStyle::Singleton = nullptr;

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon12x12(12.0f, 12.0f);
const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

/*
: FSlateStyleSet("KSkillAssetEditorStyle")
{
//TODO: 查找路径
const FString BaseDir = IPluginManager::Get().FindPlugin("KSkillFramework")->GetBaseDir();
SetContentRoot(BaseDir / TEXT("Resouces"));

FSlateStyleRegistry::RegisterSlateStyle(*this);
}
 */

FCustomAssetEditorStyle::FCustomAssetEditorStyle()
{
}

FCustomAssetEditorStyle::~FCustomAssetEditorStyle()
{
	// FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

ISlateStyle& FCustomAssetEditorStyle::Get()
{
	return *Singleton;
}

void FCustomAssetEditorStyle::Initialize()
{
	if (!Singleton.IsValid())
	{
		Singleton = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*Singleton);
	}
}

void FCustomAssetEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*Singleton);
	ensure(Singleton.IsUnique());
	Singleton.Reset();
}

FName FCustomAssetEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("KSkillAssetEditorStyle"));
	return StyleSetName;
}

const FSlateBrush* FCustomAssetEditorStyle::GetBrush(FName BrushName)
{
	if (Singleton.IsValid())
	{
		return Singleton->GetBrush(BrushName);
	}

	return nullptr;
}

void FCustomAssetEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

TSharedRef<FSlateStyleSet> FCustomAssetEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CustomAsset")->GetBaseDir() / TEXT("Resources"));
	Style->Set("CustomAssetEditorModule.OpenSKBrowserWindow", new IMAGE_BRUSH(TEXT("Icons/Icon128"), Icon40x40));
	Style->Set("CustomAssetEditor.SyncServer", new IMAGE_BRUSH(TEXT("Icons/IconSync"), Icon40x40));
	Style->Set("CustomAssetEditor.PreviewPlay", new IMAGE_BRUSH(TEXT("Icons/UI_Btn_Battle_Replay_Play_01"), Icon40x40));
	Style->Set("CustomAssetEditor.PreviewStop", new IMAGE_BRUSH(TEXT("Icons/UI_Btn_Battle_Replay_Pause_01"), Icon40x40));
	Style->Set("CustomAssetEditor.PreviewForward", new IMAGE_BRUSH(TEXT("Icons/UI_Btn_Battle_Replay_Forward_01"), Icon40x40));
	Style->Set("CustomAssetEditor.PreviewBackward", new IMAGE_BRUSH(TEXT("Icons/UI_Btn_Battle_Replay_Back_01"), Icon40x40));
	Style->Set("CustomAssetEditor.PreviewReset", new IMAGE_BRUSH(TEXT("Icons/UI_Btn_Battle_Replay_Replay_01"), Icon40x40));
	Style->Set("CustomAssetEditor.CastInGame", new IMAGE_BRUSH(TEXT("Icons/Icon_Town_play01"), Icon40x40));
	Style->Set("CustomAssetEditor.LoadGameUI", new IMAGE_BRUSH(TEXT("Icons/ICON_Options_08"), Icon40x40));
	Style->Set("CustomAssetEditor.Timeline", new BOX_BRUSH("Brushes/TrackBackground", FMargin(4.0f / 16.0f)));
	Style->Set("CustomAssetEditor.TimelineStatus", new BOX_BRUSH("Brushes/StatusBackground", FMargin(4.0f / 16.0f)));
	Style->Set("CustomAssetEditor.Node", new BOX_BRUSH("Brushes/RoundedNodeBackground", FMargin(4.0f / 16.0f)));
	Style->Set("CustomAssetEditor.NodeHighlight", new BOX_BRUSH("Brushes/RoundedNodeBackgroundHi", FMargin(4.0f / 16.0f)));
	Style->Set("CustomAssetEditor.NodeText", new BOX_BRUSH("Brushes/NodeText", FMargin(4.0f / 16.0f)));
	Style->Set("CustomAssetEditor.TimelimeStatus", new IMAGE_BRUSH(TEXT("Icons/StatusBackground"), Icon12x12));
	Style->Set("CustomAssetEditor.TimelimeStatus.Marker", new IMAGE_BRUSH(TEXT("Icons/Marker"), Icon12x12));
	Style->Set("CustomAssetEditor.TimelimeStatus.MarkerCapture", new IMAGE_BRUSH(TEXT("Icons/MarkerCapture"), Icon12x12));
	Style->Set("CustomAssetEditor.Layout.Programmer", new IMAGE_BRUSH(TEXT("Icons/Programmer"), Icon40x40));
	Style->Set("CustomAssetEditor.Layout.Designer", new IMAGE_BRUSH(TEXT("Icons/Designer"), Icon40x40));
	Style->Set("CustomAssetEditor.Layout.Artist", new IMAGE_BRUSH(TEXT("Icons/Artist"), Icon40x40));
	
	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT