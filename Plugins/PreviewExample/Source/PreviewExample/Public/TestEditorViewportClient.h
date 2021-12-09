// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FTestPreviewScene;
class STestEditorViewport;
/**
 * 
 */
class FTestEditorViewportClient : public FEditorViewportClient
{
public:
	/** FEditorViewportClient 接口 */
	FTestEditorViewportClient(FEditorModeTools* InModeTools, FTestPreviewScene* InPreviewScene = nullptr,
	                          const TWeakPtr<STestEditorViewport>& InEditorViewportWidget = nullptr);
	virtual ~FTestEditorViewportClient() override;
	void AddStaticCube();
	virtual void Tick(float DeltaSeconds) override;

private:
	TWeakPtr<STestEditorViewport> TestEditorViewport;
	FTestPreviewScene* TestPreviewScene;
	AActor* MainActor;
};
