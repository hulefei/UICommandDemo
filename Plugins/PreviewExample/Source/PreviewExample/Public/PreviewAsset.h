// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PreviewAsset.generated.h"

/**
 * 
 */
UCLASS()
class PREVIEWEXAMPLE_API UPreviewAsset : public UObject, public IInterface_PreviewMeshProvider
{
	GENERATED_BODY()
public:
	virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true) override;

	/** Get the preview mesh for this asset */
	virtual USkeletalMesh* GetPreviewMesh() const override;

	/** 
	* Get the preview mesh for this asset, non const. Allows the preview mesh to be modified if it is somehow invalid 
	* @param	bFindIfNotSet	If true, attempts to find a suitable asset if one is not found
	*/
	virtual USkeletalMesh* GetPreviewMesh(bool bFindIfNotSet = false) { return static_cast<const IInterface_PreviewMeshProvider*>(this)->GetPreviewMesh(); }

private:
	UPROPERTY()
	USkeletalMesh* PreviewSkeletalMesh = nullptr;
};
