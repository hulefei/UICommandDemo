#pragma once
#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class STestEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(STestEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	STestEditorViewport();

public:
	// ICommonEditorViewportToolbarInfoProvider interface
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	// End of ICommonEditorViewportToolbarInfoProvider interface
	
protected:
	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	//添加asset Editor 或 level Editor 通用工具栏
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;

private:
	TSharedPtr<class FTestPreviewScene> PreviewScene;
	TSharedPtr<class STestEditorViewport> TestEditorViewport;
};
