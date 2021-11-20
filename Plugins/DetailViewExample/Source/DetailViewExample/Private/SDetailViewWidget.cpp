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
	UDetailObject* DetailObject = NewObject<UDetailObject>();
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
			SNew(STextBlock).Text(WidgetText)
		]
	];
}

#undef LOCTEXT_NAMESPACE
