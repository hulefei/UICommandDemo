// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SerializationObjectMain.generated.h"

/**
 * 
 */
UCLASS()
class SERIALIZATIONOBJECT_API USerializationObjectMain : public UObject
{
	GENERATED_BODY()

public:
	static void Main();
	static void CreateTextureAsset(FString TextureName, int32 TextureWidth, int32 TextureHeight);
};
