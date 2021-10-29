// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CustomAsset.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

/**
 * 
 */
class CUSTOMASSETEDITOR_API SCustomAssetEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomAssetEditor) { }

	SLATE_END_ARGS()


public:
	/** Virtual destructor. */
	virtual ~SCustomAssetEditor();
	/**
	* Construct this widget
	*
	* @param InArgs The declaration data for this widget.
	* @param InTextAsset The UTextAsset asset to edit.
	* @param InStyleSet The style set to use.
	*/
	void Construct(const FArguments& InArgs, UCustomAsset* InTextAsset);

private:

	/** Callback for text changes in the editable text box. */
	void HandleEditableTextBoxTextChanged(const FText& NewText);

	/** Callback for committed text in the editable text box. */
	void HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType);

	/** Callback for property changes in the text asset. */
	void HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);

	private:

	/** Holds the editable text box widget. */
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;

	/** Pointer to the text asset that is being edited. */
	UCustomAsset* CustomAsset = nullptr;
};
