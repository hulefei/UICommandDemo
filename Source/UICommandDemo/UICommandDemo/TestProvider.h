﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TestProvider.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTestProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UICOMMANDDEMO_API ITestProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool ReactToTrigger();
};
