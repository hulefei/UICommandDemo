// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KSkillHello.generated.h"

/**
 * 
 */
UCLASS()
class KSKILLCORE_API UKSkillHello : public UObject
{
	GENERATED_BODY()

public:
	static void SayHello()
	{
		UE_LOG(LogTemp, Log, TEXT("UKSkillHello::SayHello"));
	}
};
