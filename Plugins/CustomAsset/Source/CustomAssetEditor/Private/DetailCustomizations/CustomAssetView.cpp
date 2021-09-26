// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetView.h"

#include "DetailLayoutBuilder.h"
#include "IPropertyUtilities.h"
#include "DetailWidgetRow.h"

TSharedRef<IPropertyTypeCustomization> FCustomAssetView::MakeInstance()
{
	return MakeShareable( new FCustomAssetView );
}

void FCustomAssetView::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	MyStructProperty = StructPropertyHandle;
	PropUtils = StructCustomizationUtils.GetPropertyUtilities().Get();

	MyKeyNameProperty = MyStructProperty->GetChildHandle(TEXT("Text"));
	KeyValues.Reset();
	KeyValues.Add(TEXT("John"));
	KeyValues.Add(TEXT("Amy"));
	KeyValues.Add(TEXT("Peter"));

	HeaderRow.IsEnabled(TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateSP(this, &FCustomAssetView::IsEditingEnabled)))
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(SComboButton)
			.OnGetMenuContent(this, &FCustomAssetView::OnGetKeyContent)
			.ContentPadding(FMargin( 2.0f, 2.0f ))
			.IsEnabled(this, &FCustomAssetView::IsEditingEnabled)
			.ButtonContent()
			[
				SNew(STextBlock) 
				.Text(this, &FCustomAssetView::GetCurrentKeyDesc)
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		];

	MyKeyNameProperty->SetValue(KeyValues[0]);
}

void FCustomAssetView::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FCustomAssetView::OnGetKeyContent() const
{
	FMenuBuilder MenuBuilder(true, NULL);

	for (int32 Idx = 0; Idx < KeyValues.Num(); Idx++)
	{
		FUIAction ItemAction( FExecuteAction::CreateSP( const_cast<FCustomAssetView*>(this), &FCustomAssetView::OnKeyComboChange, Idx) );
		MenuBuilder.AddMenuEntry( FText::FromName( KeyValues[Idx] ), TAttribute<FText>(), FSlateIcon(), ItemAction);
	}

	return MenuBuilder.MakeWidget();
}

FText FCustomAssetView::GetCurrentKeyDesc() const
{
	FName NameValue;
	MyKeyNameProperty->GetValue(NameValue);

	const int32 KeyIdx = KeyValues.IndexOfByKey(NameValue);
	return KeyValues.IsValidIndex(KeyIdx) ? FText::FromName(KeyValues[KeyIdx]) : FText::FromName(NameValue);
}

void FCustomAssetView::OnKeyComboChange(int32 Index)
{
	if (KeyValues.IsValidIndex(Index))
	{
		// UBlackboardData* BlackboardAsset = CachedBlackboardAsset.Get();
		// if (BlackboardAsset)
		// {
		// 	const uint8 KeyID = BlackboardAsset->GetKeyID(KeyValues[Index]);
		// 	const UObject* KeyClass = BlackboardAsset->GetKeyType(KeyID);
		//
		// 	MyKeyClassProperty->SetValue(KeyClass);
		// 	MyKeyIDProperty->SetValue(KeyID);
		//
		// 	MyKeyNameProperty->SetValue(KeyValues[Index]);
		// }
	}
}

bool FCustomAssetView::IsEditingEnabled() const
{
	return PropUtils->IsPropertyEditingEnabled();
}