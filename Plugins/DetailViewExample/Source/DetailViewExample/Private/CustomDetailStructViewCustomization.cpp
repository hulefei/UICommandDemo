// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDetailStructViewCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Fonts/SlateFontInfo.h"
#include "EditorStyle.h"

TSharedRef<IPropertyTypeCustomization> FCustomDetailStructViewCustomization::MakeInstance()
{
	return MakeShareable(new FCustomDetailStructViewCustomization);
}

void FCustomDetailStructViewCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
	FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	MyStructProperty = StructPropertyHandle;
	PropUtils = StructCustomizationUtils.GetPropertyUtilities().Get();

	MyKeyNameProperty = MyStructProperty->GetChildHandle(TEXT("SelectedName"));
	KeyValues.Reset();
	KeyValues.Add(TEXT("John"));
	KeyValues.Add(TEXT("Amy"));
	KeyValues.Add(TEXT("Peter"));

	FSlateFontInfo FontInfo = IDetailLayoutBuilder::GetDetailFont();
	// FEditorStyle::GetFontStyle( TEXT("PropertyWindow.NormalFont"));
	
	HeaderRow
		//.IsEnabled(TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateSP(this, &FCustomDetailStructView::IsEditingEnabled)))
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(SComboButton)
			.OnGetMenuContent(this, &FCustomDetailStructViewCustomization::OnGetKeyContent)
			 .ContentPadding(FMargin( 2.0f, 2.0f ))
			.IsEnabled(this, &FCustomDetailStructViewCustomization::IsEditingEnabled)
			.ButtonContent()
			[
				SNew(STextBlock) 
				.Text(this, &FCustomDetailStructViewCustomization::GetCurrentKeyDesc)
				.Font(FontInfo)
			]
		];

	MyKeyNameProperty->SetValue(KeyValues[0]);
}

void FCustomDetailStructViewCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FCustomDetailStructViewCustomization::OnGetKeyContent() const
{
	FMenuBuilder MenuBuilder(true, NULL);

	for (int32 Idx = 0; Idx < KeyValues.Num(); Idx++)
	{
		FUIAction ItemAction( FExecuteAction::CreateSP( const_cast<FCustomDetailStructViewCustomization*>(this), &FCustomDetailStructViewCustomization::OnKeyComboChange, Idx) );
		MenuBuilder.AddMenuEntry( FText::FromName( KeyValues[Idx] ), TAttribute<FText>(), FSlateIcon(), ItemAction);
	}

	return MenuBuilder.MakeWidget();
}

void FCustomDetailStructViewCustomization::OnKeyComboChange(int32 Idx)
{
	UE_LOG(LogTemp, Log, TEXT("OnKeyComboChange:%d"), Idx);
	MyKeyNameProperty->SetValue(KeyValues[Idx]);
}

FText FCustomDetailStructViewCustomization::GetCurrentKeyDesc() const
{
	FName NameValue;
	MyKeyNameProperty->GetValue(NameValue);

	const int32 KeyIdx = KeyValues.IndexOfByKey(NameValue);
	return KeyValues.IsValidIndex(KeyIdx) ? FText::FromName(KeyValues[KeyIdx]) : FText::FromName(NameValue);
}

bool FCustomDetailStructViewCustomization::IsEditingEnabled() const
{
	return true;
}
