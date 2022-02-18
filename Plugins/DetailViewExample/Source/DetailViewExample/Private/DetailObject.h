// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DetailObject.generated.h"

USTRUCT(BlueprintType)
struct DETAILVIEWEXAMPLE_API FCustomDetailStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FName SelectedName;

};

UCLASS()
class DETAILVIEWEXAMPLE_API UCustomDetailObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="CustomDetail")
	FName InnerName;

	UPROPERTY(EditAnywhere, Category="CustomDetail")
	int32 InnAgeAge;
};

UCLASS()
class DETAILVIEWEXAMPLE_API UDetailObject : public UObject
{
	GENERATED_BODY()

public:
	UDetailObject(const FObjectInitializer& ObjectInitializer) : CustomDetailObject(NewObject<UCustomDetailObject>())
	{
	}

public:
	UPROPERTY(EditAnywhere, Category="DetailView")
	FName Name;
	
	UPROPERTY(EditAnywhere, Category="DetailView")
	int32 Age;

	UPROPERTY(EditAnywhere, Category="DetailView")
	FCustomDetailStruct CustomDetailStruct;
	
	UPROPERTY(EditAnywhere, Category="DetailView")
	UCustomDetailObject* CustomDetailObject;
};


