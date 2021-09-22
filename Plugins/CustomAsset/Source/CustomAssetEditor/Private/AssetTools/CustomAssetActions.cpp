// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetActions.h"

#include "CustomAsset.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

FCustomAssetActions::FCustomAssetActions()
{
}

uint32 FCustomAssetActions::GetCategories()
{
	return EAssetTypeCategories::Basic;
}

FText FCustomAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_CustomAsset", "Custom Asset");
}

UClass* FCustomAssetActions::GetSupportedClass() const
{
	return UCustomAsset::StaticClass();
}

FColor FCustomAssetActions::GetTypeColor() const
{
	return FColor::Red;
}

void FCustomAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
	
	const auto NextAnimAssets = GetTypedWeakObjectPtrs<UCustomAsset>(InObjects);
	
	MenuBuilder.AddMenuEntry(
		LOCTEXT("CustomAsset_CustomAsset", "CustomAsset"),
		LOCTEXT("CustomAsset_CustomAssetTip", "CustomAsset Tip"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=]
			{
				//TODO
				// const FText DialogText = LOCTEXT("TODO", "待实现");
				// FMessageDialog::Open(EAppMsgType::Ok, DialogText);
			}),
			FCanExecuteAction::CreateLambda([=]
			{
				return true;
			})
		)
	);
}

bool FCustomAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
