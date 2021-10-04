// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionNode.h"

#include "BranchActionNode.generated.h"

class ABridgeActor;
class UBlueprint;
/**
 * 
 */
UCLASS()
class ACTIONNODEEXAMPLE_API UBranchActionNode : public UActionNode
{
	GENERATED_BODY()

	public:
	// UBranchActionNode(const FObjectInitializer& ObjectInitializer);
	virtual void Execute() override;
	void Init();
	void Deinitialization();

	UPROPERTY()
	UBlueprint* ActionBlueprint;
	UPROPERTY()
	ABridgeActor* BridgeActor;
};
