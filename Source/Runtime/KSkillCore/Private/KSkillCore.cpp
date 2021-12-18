#include "KSkillCore.h"

#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "FKSkillCore"

void FKSkillCore::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("FKSkillCore::StartupModule"));
}

void FKSkillCore::ShutdownModule()
{
	UE_LOG(LogTemp, Log, TEXT("FKSkillCore::ShutdownModule"));
}

IMPLEMENT_MODULE(FKSkillCore, KSkillCore)
#undef LOCTEXT_NAMESPACE
