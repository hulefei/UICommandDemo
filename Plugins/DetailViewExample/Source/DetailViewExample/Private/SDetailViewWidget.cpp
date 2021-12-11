// Fill out your copyright notice in the Description page of Project Settings.


#include "SDetailViewWidget.h"

#include "DetailObject.h"
#include "IDetailsView.h"

#define LOCTEXT_NAMESPACE "SDetailViewWidget"

FTreeViewInstanceData::FTreeViewInstanceData(const FString& InPath) : DiskPath(InPath)
{
	CleanName = FPaths::GetBaseFilename(DiskPath);
	bIsDirectory = !FPaths::FileExists(DiskPath);
}

FTreeViewInstanceData::FTreeViewInstanceData(const FString& InPath, TSharedPtr<FTreeViewInstanceData>& InParent): DiskPath(InPath), Parent(InParent)
{
	CleanName = FPaths::GetBaseFilename(DiskPath);
	bIsDirectory = !FPaths::FileExists(DiskPath);
}

TSharedPtr<SWidget> FTreeViewInstanceData::CreateIcon() const
{
	FSlateColor IconColor = FSlateColor::UseForeground();
	const FSlateBrush* Brush = FEditorStyle::GetBrush(bIsDirectory ? "ContentBrowser.AssetTreeFolderOpen" : "ContentBrowser.ColumnViewAssetIcon");
	return SNew(SImage)
		.Image(Brush)
		.ColorAndOpacity(IconColor);
}

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

	SAssignNew(TreeViewPtr, STreeViewPtr)
		.TreeItemsSource(&TreeRootItems)
		.OnGenerateRow(this, &SDetailViewWidget::GenerateTreeRow)
		.ItemHeight(30)
		.SelectionMode(ESelectionMode::Multi)
		.OnGetChildren(this, &SDetailViewWidget::GetChildrenForTree)
		.ClearSelectionOnClick(false)
		.HighlightParentNodesForSelection(true);

	const FString Path(TEXT("D:\\workspace\\UnrealEngine"));
	InitTreeView(Path);
	
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
			// SNew(SButton).OnClicked(this, &SDetailViewWidget::OnPlayClicked)
			TreeViewPtr.ToSharedRef()
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

void SDetailViewWidget::InitTreeView(const FString& InRootPath)
{
	FTreeViewInstanceDataPtr Root = MakeShared<FTreeViewInstanceData>(InRootPath);
	TreeRootItems.Add(Root);
	// ConstructChildrenRecursively(Root);
	CustomConstructChildren(Root);
}

void SDetailViewWidget::CustomConstructChildren(FTreeViewInstanceDataPtr TreeItem)
{
	if (TreeItem.IsValid())
	{
		FTreeViewInstanceDataPtr Parent1 = MakeShared<FTreeViewInstanceData>(TEXT("Parent1"), TreeItem);
		TreeItem->Children.Add(Parent1);
		FTreeViewInstanceDataPtr Parent2 = MakeShared<FTreeViewInstanceData>(TEXT("Parent2"), TreeItem);
		TreeItem->Children.Add(Parent2);

		FTreeViewInstanceDataPtr Child1_1 = MakeShared<FTreeViewInstanceData>(TEXT("Child1"), TreeItem);
		Child1_1->bIsDirectory = false;
		Parent1->Children.Add(Child1_1);

		FTreeViewInstanceDataPtr Child2_1 = MakeShared<FTreeViewInstanceData>(TEXT("Child1"), TreeItem);
		Child2_1->bIsDirectory = false;
		Parent2->Children.Add(Child2_1);
		// if (Child->bIsDirectory)
		// {
		// 	//目录则递归获取其子节点信息
		// 	ConstructChildrenRecursively(Child);
		// }
	}
}

void SDetailViewWidget::ConstructChildrenRecursively(FTreeViewInstanceDataPtr TreeItem)
{
	if (TreeItem.IsValid())
	{
		//找到此目录下所有文件
		TArray<FString> FindedFiles;
		FString SearchFile = TreeItem->DiskPath + "/*.*";
		IFileManager::Get().FindFiles(FindedFiles, *SearchFile, true, true);

		for (auto&element : FindedFiles)
		{
			//构建子节点
			FString FullPath = TreeItem->DiskPath + "/" + element;
			FTreeViewInstanceDataPtr Child = FTreeViewInstanceDataPtr(new FTreeViewInstanceData(FullPath, TreeItem));
			TreeItem->Children.Add(Child);
			if (Child->bIsDirectory)
			{
				//目录则递归获取其子节点信息
				ConstructChildrenRecursively(Child);
			}
		}
	}
}

TSharedRef<ITableRow> SDetailViewWidget::GenerateTreeRow(FTreeViewInstanceDataPtr TreeItem,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	check(TreeItem.IsValid());
	//根据TreeItem构建一个Item表现的Widget
	return
		SNew(STableRow<FTreeViewInstanceDataPtr>, OwnerTable)
		[
			SNew(SBox)
			.WidthOverride(200.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					TreeItem->CreateIcon().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
				SNew(STextBlock)
				.Text(FText::FromString(TreeItem->CleanName))
				.Font(FStyleDefaults::GetFontInfo(20))
				]
			]
		];
}

void SDetailViewWidget::GetChildrenForTree(FTreeViewInstanceDataPtr TreeItem, TArray<FTreeViewInstanceDataPtr>& OutChildren)
{
	//获取TreeItem的子节点信息
	if (TreeItem.IsValid())
	{
		OutChildren = TreeItem->Children;
	}
}

#undef LOCTEXT_NAMESPACE
