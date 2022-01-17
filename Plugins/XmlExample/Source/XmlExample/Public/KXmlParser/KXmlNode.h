// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class XMLEXAMPLE_API FKXmlAttribute
{
public:
	FKXmlAttribute(const FString& InTag, const FString& InValue)
		: Tag(InTag)
		, Value(InValue)
	{
	}

	/** Gets the tag of the attribute */
	const FString& GetTag() const;

	/** Gets the value of the attribute */
	const FString& GetValue() const;
	
	/** Gets the value of the attribute */
	void SetValue(const FString& InValue);
	

private:
	/** The tag string */
	FString Tag;

	/** The value string */
	FString Value;
};

class XMLEXAMPLE_API FKXmlNode
{
	friend class FKXmlFile;

private:

	/** Default ctor, private for FKXmlFile use only */
	FKXmlNode() : NextNode(nullptr) {}
	/** No copy ctor allowed */
	FKXmlNode(const FKXmlNode& rhs): NextNode(nullptr)
	{
	}

	/** dtor */
	~FKXmlNode() { Delete(); }

private:

	/** Recursively deletes the nodes for cleanup */
	void Delete();

public:

	/** Gets the next node in a list of nodes */
	const FKXmlNode* GetNextNode() const;
	/** Gets a list of children nodes */
	const TArray<FKXmlNode*>& GetChildrenNodes() const;
	/** Gets the first child of this node which can be iterated into with GetNextNode */
	const FKXmlNode* GetFirstChildNode() const;
	/** Finds the first child node that contains the specified tag */
	const FKXmlNode* FindChildNode(const FString& InTag) const;
	/** Finds the first child node that contains the specified tag */
	FKXmlNode* FindChildNode(const FString& InTag);
	/** Gets the tag of the node */
	const FString& GetTag() const;
	/** Gets the value of the node */
	const FString& GetContent() const;
	/** Sets the new value of the node */
	void SetContent(const FString InContent);

	/**
	 * Gets all of the attributes in this node
	 *
	 * @return	List of attributes in this node
	 */
	const TArray<FKXmlAttribute>& GetAttributes() const
	{
		return Attributes;
	}

	/** Gets an attribute that corresponds with the passed-in tag */
	FString GetAttribute(const FString& InTag) const;
	void UpdateOrAddAttribute(const FString& InTag, const FString& InValue);
	/** Adds a simple tag with content to the current node */
	void AppendChildNode(const FString& InTag, const FString& InContent);
private:

	/** The list of children nodes */
	TArray<FKXmlNode*> Children;
	/** Attributes of this node */
	TArray<FKXmlAttribute> Attributes;
	/** Tag of the node */
	FString Tag;
	/** Content of the node */
	FString Content;
	/** Next pointer */
	FKXmlNode* NextNode;
};
