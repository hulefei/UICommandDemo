// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

FCustomAssetCustomization::FCustomAssetCustomization()
{
}

void FCustomAssetCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	DetailLayoutBuilder = &DetailBuilder;

	// DetailBuilder.HideCategory(TEXT("NewAsset"));
	
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() != 1)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("FCustomAssetCustomization::CustomizeDetails:%d"), Objects.Num());

	auto LambdaReName = [&](FName CategoryName, FName PropertyName, FText RePropertyName)
	{
		IDetailCategoryBuilder & Category = DetailLayoutBuilder->EditCategory(CategoryName);
		const TSharedPtr<IPropertyHandle> PropertyHandle = DetailLayoutBuilder->GetProperty(PropertyName);
		IDetailPropertyRow & FilePathRow = Category.AddProperty(PropertyHandle);
		FilePathRow.CustomWidget(false)
				.NameContent()
			[
				SNew(STextBlock).Text(RePropertyName)
			]
			.ValueContent()
			[
				PropertyHandle->CreatePropertyValueWidget()
			];
	};

	LambdaReName(TEXT("NewAsset"), TEXT("Text"), FText::FromName(TEXT("文本1")));
}

TSharedRef<IDetailCustomization> FCustomAssetCustomization::MakeInstance()
{
	return MakeShareable(new FCustomAssetCustomization);
}

