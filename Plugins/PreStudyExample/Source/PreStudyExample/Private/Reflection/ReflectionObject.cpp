// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionObject.h"

#include "TargetObject.h"

void UReflectionObject::Main()
{
	UTargetObject* TargetObject = NewObject<UTargetObject>();
	UE_LOG(LogTemp, Log, TEXT("Age:%d"), TargetObject->Age);
}
