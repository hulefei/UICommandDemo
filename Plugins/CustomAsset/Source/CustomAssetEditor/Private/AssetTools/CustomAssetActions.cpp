// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetActions.h"

#include "CustomAsset.h"
#include "Toolkits/CustomAssetEditorToolkit.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

FCustomAssetActions::FCustomAssetActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{ }

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

	auto CustomAssets = GetTypedWeakObjectPtrs<UCustomAsset>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("TextAsset_ReverseText", "Reverse Text"),
		LOCTEXT("TextAsset_ReverseTextToolTip", "Reverse the text stored in the selected text asset(s)."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=]{
				for (auto& CustomAsset : CustomAssets)
				{
					if (CustomAsset.IsValid() && !CustomAsset->Text.IsEmpty())
					{
						CustomAsset->Text = FText::FromString(CustomAsset->Text.ToString().Reverse());
						CustomAsset->PostEditChange();
						CustomAsset->MarkPackageDirty();
					}
				}
			}),
			FCanExecuteAction::CreateLambda([=] {
				for (auto& CustomAsset : CustomAssets)
				{
					if (CustomAsset.IsValid() && !CustomAsset->Text.IsEmpty())
					{
						return true;
					}
				}
				return false;
			})
		)
	);
}

bool FCustomAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

void FCustomAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		                                ? EToolkitMode::WorldCentric
		                                : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		const auto CustomAsset = Cast<UCustomAsset>(*ObjIt);

		if (CustomAsset != nullptr)
		{
			TSharedRef<FCustomAssetEditorToolkit> EditorToolkit = MakeShareable(new FCustomAssetEditorToolkit(Style));
			EditorToolkit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
		}
	}
}

#undef LOCTEXT_NAMESPACE
