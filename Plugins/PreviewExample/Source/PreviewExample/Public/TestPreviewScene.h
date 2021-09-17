﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PreviewScene.h"


/**
 * 
 */
class FTestPreviewScene : public FPreviewScene
{
public:
	FTestPreviewScene(ConstructionValues CVS);

private:
	void CreateSkySphere();
	void CreateFloor();
};