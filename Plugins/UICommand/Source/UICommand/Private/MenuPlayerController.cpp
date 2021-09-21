// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"

#include "MenuHUD.h"

void AMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		//在项目设置里设置对应的按键
		InputComponent->BindAction("OpenMenu", IE_Pressed, this, &AMenuPlayerController::OpenMenu);
	}
}

void AMenuPlayerController::OpenMenu()
{
	if (AMenuHUD* MenuHUD = GetHUD<AMenuHUD>())
	{
		MenuHUD->ShowMenu();
	}
}


