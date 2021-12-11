// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "IDetailsView.h"
class UDetailObject;
/**
 * 
 */

class FTreeViewInstanceData
{
public:
	//用于构造根节点
	FTreeViewInstanceData(const FString& InPath);

	//用于构造子节点
	FTreeViewInstanceData(const FString& InPath, TSharedPtr<FTreeViewInstanceData>&InParent);

	//获得条目标志的Icon，用于区分目录还是文件
	TSharedPtr<SWidget> CreateIcon() const;

public:
	// 目标路径
	FString DiskPath;

	// 路径最后的名字，如D:\Program Files (x86)\PVS-Studio，Name=PVS-Studio，若路径指向一个文件，则Name是不带扩展名的文件名 
	FString CleanName;

	// 标志DiskPath指向的是一个文件还是目录
	bool bIsDirectory;

	//记录此节点对应的父节点
	TSharedPtr<FTreeViewInstanceData> Parent;

	//记录此节点对应的所有子节点
	TArray<TSharedPtr<FTreeViewInstanceData>> Children;
};

class DETAILVIEWEXAMPLE_API SDetailViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDetailViewWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	FReply OnPlayClicked() const;

private:
	TSharedPtr<IDetailsView> DetailsView;
	UDetailObject* DetailObject = nullptr;

	void OnFinishedChangingProperties(const FPropertyChangedEvent& Event);
	bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;

private:
	typedef TSharedPtr<FTreeViewInstanceData> FTreeViewInstanceDataPtr;
	typedef STreeView<FTreeViewInstanceDataPtr> STreeViewPtr;
	
	//根据根目录路径初始化TreeRootItems
	void InitTreeView(const FString& InRootPath);
	void CustomConstructChildren(FTreeViewInstanceDataPtr TreeItem);

	void ConstructChildrenRecursively(FTreeViewInstanceDataPtr TreeItem);

	//创建TreeItem的函数
	TSharedRef<ITableRow> GenerateTreeRow(FTreeViewInstanceDataPtr TreeItem, const TSharedRef<STableViewBase>& OwnerTable);

	//获取某个节点的子节点信息
	void GetChildrenForTree(FTreeViewInstanceDataPtr TreeItem, TArray< FTreeViewInstanceDataPtr >& OutChildren);
private:
	//实际的TreeView
	TSharedPtr<STreeViewPtr> TreeViewPtr;

	//包含所有根节点的数组
	TArray<FTreeViewInstanceDataPtr> TreeRootItems;
};
