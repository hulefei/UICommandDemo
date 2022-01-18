// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestProvider.h"
#include "UObject/Object.h"
#include "TestObject.generated.h"

/**
 * 
 */
UCLASS()
class UICOMMANDDEMO_API UTestObject : public UObject, public ITestProvider
{
	GENERATED_BODY()

public:
	void Test1(UParticleSystem* ParticleSystem);

	virtual bool ReactToTrigger() override;
};
