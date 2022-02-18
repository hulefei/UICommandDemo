// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDetailStructCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Fonts/SlateFontInfo.h"
#include "EditorStyle.h"

TSharedRef<IPropertyTypeCustomization> FCustomDetailStructCustomization::MakeInstance()
{
	return MakeShareable(new FCustomDetailStructCustomization);
}

void FCustomDetailStructCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
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
			.OnGetMenuContent(this, &FCustomDetailStructCustomization::OnGetKeyContent)
			 .ContentPadding(FMargin( 2.0f, 2.0f ))
			.IsEnabled(this, &FCustomDetailStructCustomization::IsEditingEnabled)
			.ButtonContent()
			[
				SNew(STextBlock) 
				.Text(this, &FCustomDetailStructCustomization::GetCurrentKeyDesc)
				.Font(FontInfo)
			]
		];

	MyKeyNameProperty->SetValue(KeyValues[0]);
}

void FCustomDetailStructCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FCustomDetailStructCustomization::OnGetKeyContent() const
{
	FMenuBuilder MenuBuilder(true, NULL);

	for (int32 Idx = 0; Idx < KeyValues.Num(); Idx++)
	{
		FUIAction ItemAction( FExecuteAction::CreateSP( const_cast<FCustomDetailStructCustomization*>(this), &FCustomDetailStructCustomization::OnKeyComboChange, Idx) );
		MenuBuilder.AddMenuEntry( FText::FromName( KeyValues[Idx] ), TAttribute<FText>(), FSlateIcon(), ItemAction);
	}

	return MenuBuilder.MakeWidget();
}

void FCustomDetailStructCustomization::OnKeyComboChange(int32 Idx)
{
	UE_LOG(LogTemp, Log, TEXT("OnKeyComboChange:%d"), Idx);
	MyKeyNameProperty->SetValue(KeyValues[Idx]);
}

FText FCustomDetailStructCustomization::GetCurrentKeyDesc() const
{
	FName NameValue;
	MyKeyNameProperty->GetValue(NameValue);

	const int32 KeyIdx = KeyValues.IndexOfByKey(NameValue);
	return KeyValues.IsValidIndex(KeyIdx) ? FText::FromName(KeyValues[KeyIdx]) : FText::FromName(NameValue);
}

bool FCustomDetailStructCustomization::IsEditingEnabled() const
{
	return true;
}
