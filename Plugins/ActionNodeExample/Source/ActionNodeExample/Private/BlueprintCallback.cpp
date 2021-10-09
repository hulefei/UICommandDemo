// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintCallback.h"

#include "ActionNodeLogs.h"

bool UBlueprintCallback::BranchFunction_Implementation(FName EventName)
{
	UE_LOG(LogActionNode, Log, TEXT("BranchFunction Not Implementation"));
	return false;
}
