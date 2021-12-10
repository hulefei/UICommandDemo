// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PreviewScene.h"
#include "AdvancedPreviewScene.h"
#include "IPersonaPreviewScene.h"

/**
 * 
 */
class FTestPreviewScene :  public IPersonaPreviewScene //public FAdvancedPreviewScene,
{
public:
	FTestPreviewScene(ConstructionValues CVS, float InFloorOffset = 0.0f);


	//~ override IPersonaPreviewScene
	virtual UDebugSkelMeshComponent* GetPreviewMeshComponent() const override { return SkeletalMeshComponent; }
	virtual void SetPreviewMeshComponent(UDebugSkelMeshComponent* InSkeletalMeshComponent) override;

private:
	/** The one and only actor we have */
	AActor* Actor;

	/** The main preview skeletal mesh component */
	UDebugSkelMeshComponent*			SkeletalMeshComponent;

private:
	void CreateSkySphere();
	void CreateFloor();
	
};
