// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MySerializationObject2.generated.h"

/**
 * 
 */
UCLASS()
class SERIALIZATIONOBJECT_API UMySerializationObject2 : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Name;
	
};
