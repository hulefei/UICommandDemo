// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEditorViewportClient.h"


FTestEditorViewportClient::FTestEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene,
                                                     const TWeakPtr<SEditorViewport>& InEditorViewportWidget) :
	FEditorViewportClient(InModeTools, InPreviewScene, InEditorViewportWidget)
{
	SetRealtime(true);

	const FVector DefaultPerspectiveViewLocation( 83.f, 223.5f, 136.5f );
	const FRotator DefaultPerspectiveViewRotation( -6.6f, -102.0f, 0 );
	
	//Initiate view
	SetViewLocation(DefaultPerspectiveViewLocation);
	SetViewRotation(DefaultPerspectiveViewRotation);
}

FTestEditorViewportClient::~FTestEditorViewportClient()
{
}

void FTestEditorViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}
