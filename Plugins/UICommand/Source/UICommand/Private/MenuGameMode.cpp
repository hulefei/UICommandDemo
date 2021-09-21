// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

#include "MenuHUD.h"
#include "MenuPlayerController.h"


// Sets default values
AMenuGameMode::AMenuGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
   
	//初始化自定义类
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}

// Called when the game starts or when spawned
void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMenuGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

