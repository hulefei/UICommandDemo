#include "STestEditorViewport.h"

#include "IPersonaToolkit.h"
#include "PersonaModule.h"
#include "PreviewAsset.h"
#include "TestEditorViewportClient.h"
#include "TestPreviewScene.h"
#include "IPersonaPreviewScene.h"


void STestEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

STestEditorViewport::STestEditorViewport()
{
}

TSharedRef<SEditorViewport> STestEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> STestEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void STestEditorViewport::OnFloatingButtonClicked()
{
}

TSharedRef<FEditorViewportClient> STestEditorViewport::MakeEditorViewportClient()
{
	//使用自定义
	// PreviewScene = MakeShareable(new FPreviewScene(FPreviewScene::ConstructionValues()));
	// PreviewScene = MakeShareable(new FTestPreviewScene(FPreviewScene::ConstructionValues()));
	
	const FPersonaToolkitArgs PersonaToolkitArgs;
	// PersonaToolkitArgs.OnPreviewSceneCreated.Bind();
	PreviewScene = CreatePreviewScene(PersonaToolkitArgs);
	check(PreviewScene)

	//使用默认
	// PreviewScene = MakeShareable(new FPreviewScene());

	//使用UE4默认的FEditorViewportClient，并使用PreviewScene的world, 默认使用编辑器中打开的默认场景
	// const TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr,
	//                                                                                                        PreviewScene.Get()));
	//使用自定义FEditorViewportClient
	const TSharedPtr<FTestEditorViewportClient> EditorViewportClient = MakeShareable(new FTestEditorViewportClient(
		nullptr,
		PreviewScene.Get()
		, SharedThis(this)));

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> STestEditorViewport::MakeViewportToolbar()
{
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}

TSharedRef<IPersonaPreviewScene> STestEditorViewport::CreatePreviewScene(const FPersonaToolkitArgs& PersonaToolkitArgs)
{
	FPersonaModule& PersonaModule = FModuleManager::GetModuleChecked<FPersonaModule>("Persona");
	// ersonaToolkitArgs.OnPreviewSceneCreated = FOnPreviewSceneCreated::FDelegate::CreateSP(this, &FControlRigEditor::HandlePreviewSceneCreated);
	UPreviewAsset* PreviewAsset = NewObject<UPreviewAsset>();
	// USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("Skeleton'/Game/FightingAnimsetPro/UE4_Mannequin/Mesh/UE4_Mannequin_Skeleton.UE4_Mannequin_Skeleton'"));
	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/FightingAnimsetPro/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	PreviewAsset->SetPreviewMesh(SkeletalMesh);
	const TSharedRef<IPersonaToolkit> PersonaToolkit = PersonaModule.CreatePersonaToolkit(PreviewAsset, PersonaToolkitArgs);
	auto LocalPreviewScene = PersonaToolkit->GetPreviewScene();
	return LocalPreviewScene;
}
