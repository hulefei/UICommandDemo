// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDetailObjectCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FCustomDetailObjectCustomization::MakeInstance()
{
	return MakeShareable(new FCustomDetailObjectCustomization);
}

void FCustomDetailObjectCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& DetailCategoryBuilder = DetailBuilder.EditCategory(FName("CustomCategory"));
	DetailCategoryBuilder.AddCustomRow(FText::GetEmpty())
	                     .NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString("CustomName"))
		]
		.ValueContent()
		[
			SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("NoBorder"))
				.Padding(FMargin(0, 0, 5, 0))
			[
				SNew(SEditableTextBox)
					// .Text(this, &FCustomDetailObjectCustomization::OnGetGroupText)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
					.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		];
}

FText FCustomDetailObjectCustomization::OnGetGroupText() const
{
	return FText::FromName(TEXT("NameValue"));
}

