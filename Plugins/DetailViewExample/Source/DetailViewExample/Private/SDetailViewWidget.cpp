// Fill out your copyright notice in the Description page of Project Settings.


#include "SDetailViewWidget.h"

#include "DetailObject.h"
#include "IDetailsView.h"

#define LOCTEXT_NAMESPACE "SDetailViewWidget"

void SDetailViewWidget::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false);
	// DetailsViewArgs.NotifyHook = this;
	DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailObject = NewObject<UDetailObject>();

	DetailsView->OnFinishedChangingProperties().AddSP(this, &SDetailViewWidget::OnFinishedChangingProperties);
	DetailsView->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateSP(this, &SDetailViewWidget::IsPropertyVisible));

	DetailsView->SetObject(DetailObject);
	
	const FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDetailViewExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("DetailViewExample.cpp"))
	);
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().FillWidth(0.3f)
		[
			DetailsView.ToSharedRef()
		]
		+ SHorizontalBox::Slot().FillWidth(0.7f)
		[
			// SNew(STextBlock).Text(WidgetText)
			SNew(SButton).OnClicked(this, &SDetailViewWidget::OnPlayClicked)
		]
	];
}

FReply SDetailViewWidget::OnPlayClicked() const
{
	UE_LOG(LogTemp, Log, TEXT("SelectedName：%s"), *DetailObject->CustomDetailStruct.SelectedName.ToString());
	return FReply::Handled();
}

void SDetailViewWidget::OnFinishedChangingProperties(const FPropertyChangedEvent& Event)
{
	const FProperty* Property = Event.Property;
	const FString Name = Property->GetName();
	UE_LOG(LogTemp, Log, TEXT("Name:%s"), *FString(Name));
}


bool SDetailViewWidget::IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const
{
	UE_LOG(LogTemp, Log, TEXT("SDetailViewWidget::IsPropertyVisible"));
	const FProperty& Property = PropertyAndParent.Property;
 
	static const FName MetaName = "TestShow";
	if (Property.HasMetaData(MetaName))
	{
		TArray<FString> MetaString;
		Property.GetMetaData(MetaName).ParseIntoArray(MetaString, TEXT(","), true);
		if(MetaString.Contains("222")) return false;
	}
 
	return true;
}


#undef LOCTEXT_NAMESPACE
