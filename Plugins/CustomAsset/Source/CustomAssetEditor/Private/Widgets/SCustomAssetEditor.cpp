// Fill out your copyright notice in the Description page of Project Settings.


#include "SCustomAssetEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "CustomAsset.h"
#include "Shared/CustomAssetEditorSettings.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

// #include "TextAssetEditorSettings.h"


#define LOCTEXT_NAMESPACE "STextAssetEditor"


/* STextAssetEditor interface
 *****************************************************************************/

SCustomAssetEditor::~SCustomAssetEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void SCustomAssetEditor::Construct(const FArguments& InArgs, UCustomAsset* InCustomAsset)
{
	CustomAsset = InCustomAsset;

	auto Settings = GetDefault<UCustomAssetEditorSettings>();

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SAssignNew(EditableTextBox, SMultiLineEditableTextBox)
					.BackgroundColor((Settings != nullptr) ? Settings->BackgroundColor : FLinearColor::White)
					.Font((Settings != nullptr) ? Settings->Font : FSlateFontInfo())
					.ForegroundColor((Settings != nullptr) ? Settings->ForegroundColor : FLinearColor::Black)
					.Margin((Settings != nullptr) ? Settings->Margin : 4.0f)
					.OnTextChanged(this, &SCustomAssetEditor::HandleEditableTextBoxTextChanged)
					.OnTextCommitted(this, &SCustomAssetEditor::HandleEditableTextBoxTextCommitted)
					.Text(CustomAsset->Text)
			]
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SCustomAssetEditor::HandleTextAssetPropertyChanged);
}


/* STextAssetEditor callbacks
 *****************************************************************************/

void SCustomAssetEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	CustomAsset->MarkPackageDirty();
}


void SCustomAssetEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	CustomAsset->Text = EditableTextBox->GetText();
}


void SCustomAssetEditor::HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == CustomAsset)
	{
		EditableTextBox->SetText(CustomAsset->Text);
	}
}


#undef LOCTEXT_NAMESPACE
