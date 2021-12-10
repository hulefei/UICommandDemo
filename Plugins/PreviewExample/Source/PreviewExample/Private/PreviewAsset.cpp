// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewAsset.h"

void UPreviewAsset::SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty)
{
	PreviewSkeletalMesh = PreviewMesh;
}

USkeletalMesh* UPreviewAsset::GetPreviewMesh() const
{
	return PreviewSkeletalMesh;
}
