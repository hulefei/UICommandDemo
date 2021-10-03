// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TICKEXAMPLE_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	public://重载的函数，可以做一些初始化和释放操作
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;
	public:
	UFUNCTION(BlueprintCallable)
	void AddScore(float delta);
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Score;
};
