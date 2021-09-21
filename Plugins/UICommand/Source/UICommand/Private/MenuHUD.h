// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

UCLASS()
class UICOMMAND_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	
	protected:
	virtual void BeginPlay() override;
	
	protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;   //要显示的菜单窗口
	TSharedPtr<class SWidget> MenuWidgetContainer;

	public:
	void ShowMenu();    //显示菜单
	void RemoveMenu();  //移除菜单

	
};
