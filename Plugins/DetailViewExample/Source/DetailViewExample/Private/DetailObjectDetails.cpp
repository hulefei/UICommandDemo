// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailObjectDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FDetailObjectDetails::MakeInstance()
{
	return MakeShareable( new FDetailObjectDetails );
}

void FDetailObjectDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& aaa = DetailBuilder.EditCategory(FName("aaa"));
	aaa.AddCustomRow(FText::GetEmpty())
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("sss"))
	]
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("abc"))
	];

}
