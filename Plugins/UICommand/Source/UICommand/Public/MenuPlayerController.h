// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuPlayerController.generated.h"

UCLASS()
class UICOMMAND_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
private:
	void OpenMenu();
	void CloseMenu();
};
