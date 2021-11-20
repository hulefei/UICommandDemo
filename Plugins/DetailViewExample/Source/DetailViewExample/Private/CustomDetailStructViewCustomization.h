// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DETAILVIEWEXAMPLE_API FCustomDetailStructViewCustomization : public IPropertyTypeCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle,
	                             class FDetailWidgetRow& HeaderRow,
	                             IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle,
	                               class IDetailChildrenBuilder& StructBuilder,
	                               IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	TSharedRef<SWidget> OnGetKeyContent() const;
	void OnKeyComboChange(int32 Idx);
	FText GetCurrentKeyDesc() const;
	bool IsEditingEnabled() const;

private:
	TSharedPtr<IPropertyHandle> MyStructProperty;
	IPropertyUtilities* PropUtils = nullptr;
	TSharedPtr<IPropertyHandle> MyKeyNameProperty;
	TArray<FName> KeyValues;
};
