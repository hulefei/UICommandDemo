#pragma once

#include "ActionData.generated.h"

UENUM()
enum class FActionType : uint8
{
	None,
	Entry,
	Branch,
	Print
};

USTRUCT()
struct FActionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 Id = 0;

	UPROPERTY()
	FName Name = FName(TEXT("None"));

	UPROPERTY()
	FActionType Type = FActionType::None;

	UPROPERTY()
	FString AssetReferenceString;

	UPROPERTY()
	TArray<int32> Next;
};
