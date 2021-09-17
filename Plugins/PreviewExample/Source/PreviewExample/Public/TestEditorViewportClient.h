// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FTestEditorViewportClient : public FEditorViewportClient
{
public:
	/** FEditorViewportClient 接口 */
	FTestEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene = nullptr,
	                          const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);
	virtual ~FTestEditorViewportClient() override;
	virtual void Tick(float DeltaSeconds) override;
};
