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
	FTestEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene = nullptr,
	                          const TWeakPtr<STestEditorViewport>& InEditorViewportWidget = nullptr);
	virtual ~FTestEditorViewportClient() override;
	void AddStaticCube();
	void AddStaticBlueprint();
	// void PlayAnim();
	void PlayMontage();
	UAnimSingleNodeInstance* GetPreviewInstance() const;
	void ReverseAnim();
	void StopMontage();
	void AddStaticSkeletalMesh();
	virtual void Tick(float DeltaSeconds) override;

private:
	TWeakPtr<STestEditorViewport> TestEditorViewport;
	FTestPreviewScene* TestPreviewScene;
	ACharacter* MainActor;
	UAnimMontage* Montage;
};
