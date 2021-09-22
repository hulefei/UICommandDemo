// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetFactoryNew.h"

#include "CustomAsset.h"

UCustomAssetFactoryNew::UCustomAssetFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UCustomAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UCustomAssetFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                                  UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UCustomAsset>(InParent, InClass, InName, Flags);
}

bool UCustomAssetFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
