// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FTestCommands : public TCommands<FTestCommands>
{
public:
	FTestCommands();

	// TCommands<>的接口：注册命令
	virtual void RegisterCommands() override;

	//命令A
	TSharedPtr< FUICommandInfo > CommandA;
};
