// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionData.h"

#include "ActionExecutor.generated.h"

class UActionNode;
/**
 * 
 */
UCLASS()
class ACTIONNODEEXAMPLE_API UActionExecutor : public UObject
{
	GENERATED_BODY()

public:
	static UActionExecutor* New(const FActionData InEntry, const TMap<int32, FActionData>& InActionDataMap)
	{
		UActionExecutor* Target = NewObject<UActionExecutor>();
		Target->Init(InEntry, InActionDataMap);
		return Target;
	};

	bool Execute() const;
	
private:
	void Init(FActionData InEntry, TMap<int32, FActionData> InActionDataMap);
	
	FActionData Entry;
	TMap<int32, FActionData> ActionDataMap;
};
