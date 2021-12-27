// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ReflectionObject.generated.h"

/**
 * 
 */
UCLASS()
class PRESTUDYEXAMPLE_API UReflectionObject : public UObject
{
	GENERATED_BODY()

public:
	static void Main();
	static void SayHello()
	{
		UE_LOG(LogTemp, Log, TEXT("UReflectionObject Say Hello"));
	};
};
