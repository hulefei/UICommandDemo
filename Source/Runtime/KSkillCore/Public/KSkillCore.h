#pragma once
#include "Modules/ModuleInterface.h"

class UKSkillAsset;

class FKSkillCore :public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void SayHello()
	{
		UE_LOG(LogTemp, Log, TEXT("FKSkillCore::SayHello"));
	}

};
