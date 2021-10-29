// Fill out your copyright notice in the Description page of Project Settings.


#include "SCustomAssetKTimelineScrollBox.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCustomAssetKTimelineScrollBox::Construct(const FArguments& InArgs)
{
	SScrollBox::Construct(SScrollBox::FArguments().Orientation(Orient_Vertical).ScrollBarAlwaysVisible(true));
}

FReply SCustomAssetKTimelineScrollBox::OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& MouseEvent)
{
	UE_LOG(LogTemp, Log, TEXT("SKSkillSimpleTimelineScrollBox::OnMouseButtonUp"));
	return SScrollBox::OnMouseButtonUp(InGeometry, MouseEvent);
}

// TSharedRef<SWidget> SKSkillSimpleTimelineScrollBox::GenerateActionContextMenu()
// {
// 	return nullptr;
// }

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
