// Fill out your copyright notice in the Description page of Project Settings.


#include "XmlMain.h"

#include "KXmlParser/KXmlFile.h"

#define LOCTEXT_NAMESPACE "FXmlExampleModule"

void UXmlMain::Main()
{
	// FText DialogText = FText::Format(
	// 						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	// 						FText::FromString(TEXT("FXmlExampleModule::PluginButtonClicked()")),
	// 						FText::FromString(TEXT("XmlExample.cpp"))
	// 				   );
	// FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	FString XmlPath = FPaths::ProjectPluginsDir() + TEXT("XmlExample/Content/Movies.xml");
	FString XmlPath2 = FPaths::ProjectPluginsDir() + TEXT("XmlExample/Content/Movies2.xml");
	UE_LOG(LogTemp, Log, TEXT("XmlPath:%s"), *XmlPath);
	XmlPath = FPaths::ConvertRelativePathToFull(XmlPath);
	XmlPath2 = FPaths::ConvertRelativePathToFull(XmlPath2);
	if (FPaths::FileExists(XmlPath))
	{
		FKXmlFile* XmlFile = new FKXmlFile(XmlPath);
		// 获取根节点
		FKXmlNode* RootNode = XmlFile->GetRootNode();
		// 获取属性值
		FString MovieName = RootNode->GetAttribute(TEXT("Name"));

		RootNode->AppendChildNode(TEXT("Place"), TEXT("Shanghai")).UpdateOrAddAttribute(TEXT("ID"), TEXT("310"));
		RootNode->AppendChildNode(TEXT("Place")).UpdateOrAddAttribute(TEXT("ID"), TEXT("310"));
		// 获取子节点
		FKXmlNode* CategoryNode = RootNode->FindChildNode(TEXT("Category"));
		FString CategoryName = CategoryNode->GetAttribute(TEXT("Name"));
		CategoryNode->UpdateOrAddAttribute(TEXT("ID"), TEXT("28"));
		// 获取子节点的值
		FString MovieCategory = CategoryNode->GetContent();
	
		FString MovieDirector = RootNode->FindChildNode(TEXT("Director"))->GetContent();
		FString MovieTime = RootNode->FindChildNode(TEXT("Time"))->GetContent();

		XmlFile->Save(XmlPath2);
	
		UE_LOG(LogTemp, Warning, TEXT("%s\t%s\t%s\t%s\t%s\t"), *MovieName, *MovieCategory, *MovieDirector, *MovieTime, *CategoryName);
	}
}

#undef LOCTEXT_NAMESPACE
