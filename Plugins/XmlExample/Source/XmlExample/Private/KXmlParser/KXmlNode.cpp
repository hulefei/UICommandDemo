// Fill out your copyright notice in the Description page of Project Settings.


#include "KXmlParser/KXmlNode.h"


const FString& FKXmlAttribute::GetTag() const
{
	return Tag;
}

const FString& FKXmlAttribute::GetValue() const
{
	return Value;
}

void FKXmlAttribute::SetValue(const FString& InValue)
{
	Value = InValue;
}

void FKXmlNode::Delete()
{
	const int32 ChildCount = Children.Num();
	for(int32 ChildIndex = 0; ChildIndex < ChildCount; ++ChildIndex)
	{
		check(Children[ChildIndex] != nullptr);
		Children[ChildIndex]->Delete();
		delete Children[ChildIndex];
	}
	Children.Empty();
}

const FKXmlNode* FKXmlNode::GetNextNode() const
{
	return NextNode;
}

const TArray<FKXmlNode*>& FKXmlNode::GetChildrenNodes() const
{
	return Children;
}

const FKXmlNode* FKXmlNode::GetFirstChildNode() const
{
	if(Children.Num() > 0)
	{
		return Children[0];
	}
	else
	{
		return nullptr;
	}
}

const FKXmlNode* FKXmlNode::FindChildNode(const FString& InTag) const
{
	const int32 ChildCount = Children.Num();
	for(int32 ChildIndex = 0; ChildIndex < ChildCount; ++ChildIndex)
	{
		if(Children[ChildIndex] != nullptr && Children[ChildIndex]->GetTag() == InTag)
		{
			return Children[ChildIndex];
		}
	}

	return nullptr;
}

FKXmlNode* FKXmlNode::FindChildNode(const FString& InTag)
{
	return const_cast<FKXmlNode*>(AsConst(*this).FindChildNode(InTag));
}

const FString& FKXmlNode::GetTag() const
{
	return Tag;
}

const FString& FKXmlNode::GetContent() const
{
	return Content;
}

void FKXmlNode::SetContent( const FString InContent )
{
	Content = InContent;
}

FString FKXmlNode::GetAttribute(const FString& InTag) const
{
	for(auto Iter(Attributes.CreateConstIterator()); Iter; Iter++)
	{
		if(Iter->GetTag() == InTag)
		{
			return Iter->GetValue();
		}
	}
	return FString();
}

void FKXmlNode::UpdateOrAddAttribute(const FString& InTag, const FString& InValue)
{
	for (FKXmlAttribute& Attribute : Attributes)
	{
		if (Attribute.GetTag().Equals(InTag))
		{
			Attribute.SetValue(InValue);
			return;
		}
	}

	const FKXmlAttribute NewAttribute(InTag, InValue);
	Attributes.Add(NewAttribute);
}

FKXmlNode& FKXmlNode::AppendChildNode(FKXmlNode* InNode)
{
	const auto NumChildren = Children.Num();
	if (NumChildren != 0)
	{
		Children[NumChildren - 1]->NextNode = InNode;
	}
	Children.Push(InNode);

	return *InNode;
}

FKXmlNode& FKXmlNode::AppendChildNode(const FString& InTag, const FString& InContent)
{
	const auto NewNode = new FKXmlNode;
	NewNode->Tag = InTag;
	NewNode->Content = InContent;

	return AppendChildNode(NewNode);
}
