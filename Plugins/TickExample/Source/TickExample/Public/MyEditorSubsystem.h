#pragma once

#include "CoreMinimal.h"

#include "EditorSubsystem.h"

#include "MyEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TICKEXAMPLE_API UMyEditorSubsystem : public UEditorSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	// Begin UEditorSubsystem Interface.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End UEditorSubsystem Interface.

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// FORCEINLINE virtual bool IsTickableInEditor() const override {return true;}
	// End FTickableGameObject Interface.

	public:
	UFUNCTION(BlueprintCallable)
	void AddScore(float delta);
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Score;
};
