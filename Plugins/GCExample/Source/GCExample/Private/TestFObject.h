// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TestUObject.h"

class FTestFObject : FGCObject
{
public:
	
	FTestFObject()
	{
		Name = TEXT("Hello");
		TestUObject = NewObject<UTestUObject>();
		WeakObjectPtr = TestUObject;
	};

	// virtual ~FTestFObject() override;

	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

	FString Name;
	UTestUObject* TestUObject;
	TWeakObjectPtr<UTestUObject> WeakObjectPtr;
};
