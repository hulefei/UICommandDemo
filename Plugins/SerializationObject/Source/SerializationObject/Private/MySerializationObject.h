// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MySerializationObject2.h"
#include "UObject/Object.h"
#include "MySerializationObject.generated.h"

/**
 * 
 */
UCLASS()
class SERIALIZATIONOBJECT_API UMySerializationObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Age = 100;

	UPROPERTY()
	UMySerializationObject2* MySerializationObject2;
};
