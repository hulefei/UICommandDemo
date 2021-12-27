// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetObject.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

UTargetObject::UTargetObject(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
                                                                           , Age(30)
                                                                           , Name(FName(TEXT("lefeihu")))
                                                                           , Description(
	                                                                           FString(TEXT("this is a description")))
                                                                           , SoftObjectPath(FSoftObjectPath(TEXT("Class'/Game/aa'")))
{

	const TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject);
	for (TFieldIterator<FProperty> PropertyIter(GetClass()); PropertyIter; ++PropertyIter)
	{
		if (!PropertyIter->HasMetaData(TEXT("kskill"))) continue;
	
		const FProperty* PropertyIns = *PropertyIter;
		if (const FIntProperty* NumericProperty = CastField<FIntProperty>(PropertyIns))
		{
			int32 Value = NumericProperty->GetPropertyValue_InContainer(this);
			UE_LOG(LogTemp, Log, TEXT("%s : %d"), *PropertyIns->GetName(), Value);
			
			Root->SetNumberField(*PropertyIns->GetName(), Value);
			continue;
		}
		
		if (const FStrProperty* StrProperty = CastField<FStrProperty>(PropertyIns))
		{
			FString Value = StrProperty->GetPropertyValue_InContainer(this);
			UE_LOG(LogTemp, Log, TEXT("%s : %s"), *PropertyIns->GetName(), *Value);
			Root->SetStringField(*PropertyIns->GetName(), *Value);
			continue;
		}
		
		if (const FNameProperty* NameProperty = CastField<FNameProperty>(PropertyIns))
		{
			FName Value = NameProperty->GetPropertyValue_InContainer(this);
			UE_LOG(LogTemp, Log, TEXT("%s : %s"), *PropertyIns->GetName(), *Value.ToString());
			Root->SetStringField(*PropertyIns->GetName(), *Value.ToString());
			continue;
		}

		// if (const FEnumProperty* EnumProperty = CastField<FEnumProperty>(PropertyIns))
		// {
		// 	EnumProperty->GetEnum()
		// 	// FName Value = EnumProperty->GetPropertyValue_InContainer(this);
		// 	// UE_LOG(LogTemp, Log, TEXT("%s : %s"), *PropertyIns->GetName(), *Value.ToString());
		// 	// continue;
		// }

		// if (const FSoftObjectPath* SoftObjectPathPtr = PropertyIns->ContainerPtrToValuePtr<FSoftObjectPath>(this))
		// {
		// 	UE_LOG(LogTemp, Log, TEXT("%s : %s"), *PropertyIns->GetName(), *SoftObjectPathPtr->ToString());
		// 	continue;
		// }

		// if (const FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(PropertyIns))
		// {
		// 	FSoftObjectPtr Value = SoftObjectProperty->GetPropertyValue_InContainer(this);
		// 	UE_LOG(LogTemp, Log, TEXT("%s : %s"), *PropertyIns->GetName(), *Value.ToSoftObjectPath().ToString());
		// 	continue;
		// }
		UE_LOG(LogTemp, Warning, TEXT("%s 该类型不支持"), *PropertyIns->GetName());
	}

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
		
	UE_LOG(LogTemp, Log, TEXT("%s"), *OutputString);
}
