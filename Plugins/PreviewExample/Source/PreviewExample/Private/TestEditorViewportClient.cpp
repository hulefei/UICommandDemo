// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEditorViewportClient.h"


FTestEditorViewportClient::FTestEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene,
                                                     const TWeakPtr<SEditorViewport>& InEditorViewportWidget) :
	FEditorViewportClient(InModeTools, InPreviewScene, InEditorViewportWidget)
{
}

FTestEditorViewportClient::~FTestEditorViewportClient()
{
}

void FTestEditorViewportClient::Tick(float DeltaSeconds)
{
	if (DeltaSeconds > 0.f)
	{
		PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
	}
}
