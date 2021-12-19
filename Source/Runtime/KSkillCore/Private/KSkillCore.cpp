#include "KSkillCore.h"

#include "KSkillAsset.h"
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

// UKSkillAsset* FKSkillCore::GetAsset() const
// {
// 	UKSkillAsset* Asset = NewObject<UKSkillAsset>();
// 	Asset->Name = TEXT("FKSkillCore:lefeihu");
// 	return Asset;
// }

IMPLEMENT_MODULE(FKSkillCore, KSkillCore)
#undef LOCTEXT_NAMESPACE
