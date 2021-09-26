// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API FCustomAssetView : public IPropertyTypeCustomization
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


private:
	TSharedRef<SWidget> OnGetKeyContent() const;
	FText GetCurrentKeyDesc() const;
	void OnKeyComboChange(int32 Index);
	bool IsEditingEnabled() const;

	TSharedPtr<IPropertyHandle> MyStructProperty;
	TSharedPtr<IPropertyHandle> MyKeyNameProperty;
	TSharedPtr<IPropertyHandle> MyKeyIDProperty;
	TSharedPtr<IPropertyHandle> MyKeyClassProperty;

	/** cached names of keys */	
	TArray<FName> KeyValues;

	bool bNoneIsAllowedValue;


	/** property utils */
	class IPropertyUtilities* PropUtils = nullptr;
};
