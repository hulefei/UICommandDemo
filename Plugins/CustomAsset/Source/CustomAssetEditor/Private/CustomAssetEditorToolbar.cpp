// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetEditorToolbar.h"

#include "WorkflowOrientedApp/SModeWidget.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditorToolbar"

class SCustomAssetModeSeparator : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SCustomAssetModeSeparator) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArg)
	{
		SBorder::Construct(
			SBorder::FArguments()
			.BorderImage(FEditorStyle::GetBrush("BlueprintEditor.PipelineSeparator"))
			.Padding(0.0f)
			);
	}

	// SWidget interface
	virtual FVector2D ComputeDesiredSize(float) const override
	{
		const float Height = 20.0f;
		const float Thickness = 16.0f;
		return FVector2D(Thickness, Height);
	}
	// End of SWidget interface
};

void FCustomAssetEditorToolbar::AddModesToolbar(TSharedPtr<FExtender> Extender)
{
	check(CustomAssetEditor.IsValid());
	const TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();

	Extender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		CustomAssetEditorPtr->GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP( this, &FCustomAssetEditorToolbar::FillModesToolbar ) );
}

void FCustomAssetEditorToolbar::AddCustomAssetToolbar(TSharedPtr<FExtender> Extender)
{
	check(CustomAssetEditor.IsValid());
	const TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();
	Extender->AddToolBarExtension("Asset", EExtensionHook::After, CustomAssetEditorPtr->GetToolkitCommands(), FToolBarExtensionDelegate::CreateSP(this, &FCustomAssetEditorToolbar::FillCustomAssetEditorToolbar));
}


void FCustomAssetEditorToolbar::FillModesToolbar(FToolBarBuilder& ToolbarBuilder) const
{
	check(CustomAssetEditor.IsValid());
	const TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();

	const TAttribute<FName> GetActiveMode(CustomAssetEditorPtr.ToSharedRef(), &FCustomAssetEditorToolkit::GetCurrentMode);
	const FOnModeChangeRequested SetActiveMode = FOnModeChangeRequested::CreateSP(CustomAssetEditorPtr.ToSharedRef(), &FCustomAssetEditorToolkit::SetCurrentMode);

	// Left side padding
	CustomAssetEditorPtr->AddToolbarWidget(SNew(SSpacer).Size(FVector2D(4.0f, 1.0f)));

	CustomAssetEditorPtr->AddToolbarWidget(
		SNew(SModeWidget, FCustomAssetEditorToolkit::GetLocalizedMode( FCustomAssetEditorToolkit::CustomAssetMode ), FCustomAssetEditorToolkit::CustomAssetMode)
		.OnGetActiveMode(GetActiveMode)
		.OnSetActiveMode(SetActiveMode)
		// .CanBeSelected(BehaviorTreeEditorPtr.Get(), &FCustomAssetEditorToolkit::CanAccessBehaviorTreeMode)
		.ToolTipText(LOCTEXT("BehaviorTreeModeButtonTooltip", "Switch to Behavior Tree Mode"))
		.IconImage(FEditorStyle::GetBrush("BTEditor.SwitchToBehaviorTreeMode"))
		.SmallIconImage(FEditorStyle::GetBrush("BTEditor.SwitchToBehaviorTreeMode.Small"))
	);

	CustomAssetEditorPtr->AddToolbarWidget(SNew(SCustomAssetModeSeparator));

	CustomAssetEditorPtr->AddToolbarWidget(
		SNew(SModeWidget, FCustomAssetEditorToolkit::GetLocalizedMode( FCustomAssetEditorToolkit::CustomAssetMode ), FCustomAssetEditorToolkit::CustomAssetTestMode)
		.OnGetActiveMode(GetActiveMode)
		.OnSetActiveMode(SetActiveMode)
		// .CanBeSelected(BehaviorTreeEditorPtr.Get(), &FBehaviorTreeEditor::CanAccessBlackboardMode)
		.ToolTipText(LOCTEXT("BlackboardModeButtonTooltip", "Switch to Blackboard Mode"))
		.IconImage(FEditorStyle::GetBrush("BTEditor.SwitchToBlackboardMode"))
		.SmallIconImage(FEditorStyle::GetBrush("BTEditor.SwitchToBlackboardMode.Small"))
	);
		
	// Right side padding
	CustomAssetEditorPtr->AddToolbarWidget(SNew(SSpacer).Size(FVector2D(4.0f, 1.0f)));
}

void FCustomAssetEditorToolbar::FillCustomAssetEditorToolbar(FToolBarBuilder& ToolbarBuilder)
{
	check(CustomAssetEditor.IsValid());
	TSharedPtr<FCustomAssetEditorToolkit> CustomAssetEditorPtr = CustomAssetEditor.Pin();
	ToolbarBuilder.BeginSection("ExtendToolbarItem");
	{
		const FText NewNodeLabel = LOCTEXT("NewNode_Label", "New");
		const FText NewNodeTooltip = LOCTEXT("NewNode_ToolTip", "Create a new node");
		const FSlateIcon NewNodeIcon = FSlateIcon(TEXT("EditorStyle"), "SessionConsole.Clear");
	
		ToolbarBuilder.AddToolBarButton(
			FUIAction(
				FExecuteAction::CreateSP(CustomAssetEditorPtr.Get(), &FCustomAssetEditorToolkit::CreateNewNode),
				FCanExecuteAction::CreateSP(CustomAssetEditorPtr.Get(), &FCustomAssetEditorToolkit::CanCreateNewNode),
				FIsActionChecked()
			),
			NAME_None,
			NewNodeLabel,
			NewNodeTooltip,
			NewNodeIcon
		);
	}
	ToolbarBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE
