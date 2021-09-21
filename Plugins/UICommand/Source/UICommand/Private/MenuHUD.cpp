// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"

// Called when the game starts or when spawned
void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this); //把本身这个HUD类作为参数传给窗口类
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
	}
	/* PlayerController which owns this HUD. */
	if (PlayerOwner)
	{
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());  //设置输入模式
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}


