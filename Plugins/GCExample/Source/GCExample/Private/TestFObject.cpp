// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFObject.h"

// FTestFObject::~FTestFObject()
// {
// 	
// }

void FTestFObject::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(TestUObject);
}
