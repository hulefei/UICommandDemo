﻿#include "STestEditorViewport.h"

#include "TestEditorViewportClient.h"
#include "TestPreviewScene.h"


void STestEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}
STestEditorViewport::STestEditorViewport()
{
}

TSharedRef<SEditorViewport> STestEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> STestEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void STestEditorViewport::OnFloatingButtonClicked()
{
}

TSharedRef<FEditorViewportClient> STestEditorViewport::MakeEditorViewportClient()
{
	//使用自定义
	PreviewScene = MakeShareable(new FTestPreviewScene(FPreviewScene::ConstructionValues()));
	//使用默认
	// PreviewScene = MakeShareable(new FPreviewScene());

	//使用UE4默认的FEditorViewportClient，并使用PreviewScene的world, 默认使用编辑器中打开的默认场景
	// const TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr,
	//                                                                                                        PreviewScene.Get()));
	//使用自定义FEditorViewportClient
	const TSharedPtr<FTestEditorViewportClient> EditorViewportClient = MakeShareable(new FTestEditorViewportClient(nullptr,
																											PreviewScene.Get()));
	
	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> STestEditorViewport::MakeViewportToolbar()
{
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}
