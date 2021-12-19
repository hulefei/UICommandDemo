// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloEditor.h"

#include "ModuleExample.h"
#include "ModuleExampleAsset.h"

void UHelloEditor::Hello1()
{
	// FModuleExampleModule& ModuleExample = FModuleManager::Get().LoadModuleChecked<FModuleExampleModule>("ModuleExample");
	// ModuleExample.SayHello();
	UModuleExampleAsset* Asset = NewObject<UModuleExampleAsset>();
	Asset->Name = TEXT("lefeihu Editor");
}
