// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionNode.h"

#include "Engine/StreamableManager.h"

UActionNode::UActionNode(const FObjectInitializer& ObjectInitializer)
{
	StreamableManager = MakeShareable(new FStreamableManager());
}
