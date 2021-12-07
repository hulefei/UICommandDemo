// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializationObjectMain.h"

#include "MySerializationObject.h"
#include "AssetRegistry/AssetRegistryModule.h"

void USerializationObjectMain::Main()
{
	UE_LOG(LogTemp, Log, TEXT("USerializationObjectMain::Main"));

	const FString PackageName = TEXT("/Game/MySerializationObject");
	UPackage* Package = CreatePackage(*PackageName);
	
	// UMySerializationObject* MyInstance = NewObject<UMySerializationObject>(Package);
	// MyInstance->Age = 102;
	// MyInstance->MySerializationObject2 = NewObject<UMySerializationObject2>(MyInstance->GetPackage());
	// MyInstance->MySerializationObject2->Name = TEXT("lefeihu2");
	// FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName,
	//                                                                   FPackageName::GetAssetPackageExtension());
	// bool bSaved = UPackage::SavePackage(Package, MyInstance, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
	//                                     *PackageFileName, GError, nullptr, true, true, SAVE_NoError);
	// MyInstance->Rename(TEXT("MySerializationObject"));
	// UPackage::Save(Package, MyInstance, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError,
	//                nullptr, true, true, SAVE_NoError);

	UMySerializationObject* LoadedInstance = LoadObject<UMySerializationObject>(
		Package, TEXT("/Game/MySerializationObject.MySerializationObject"));

	if (LoadedInstance == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("LoadedInstance is nullptr"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("LoadedInstance is not nullptr:%d"), LoadedInstance->Age);
		if (LoadedInstance->MySerializationObject2 == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("MySerializationObject2 is nullptr"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("MySerializationObject2 is not nullptr:%s"),
			       *(LoadedInstance->MySerializationObject2->Name));
		}
	}
}

void USerializationObjectMain::CreateTextureAsset(FString TextureName, int32 TextureWidth, int32 TextureHeight)
{
	FString PackageName = TEXT("/Game/");
	PackageName += TextureName;
	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();

	UTexture2D* NewTexture = NewObject<UTexture2D>(Package, *TextureName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

	NewTexture->AddToRoot(); // This line prevents garbage collection of the texture
	NewTexture->PlatformData = new FTexturePlatformData(); // Then we initialize the PlatformData
	NewTexture->PlatformData->SizeX = TextureWidth;
	NewTexture->PlatformData->SizeY = TextureHeight;
	// NewTexture->PlatformData->NumSlices = 1;
	NewTexture->PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;

	uint8* Pixels = new uint8[TextureWidth * TextureHeight * 4];
	uint8 G = 0;
	uint8 B = 0;
	uint8 R = 255;
	uint8 A = 255;
	for (int32 y = 0; y < TextureHeight; y++)
	{
		for (int32 x = 0; x < TextureWidth; x++)
		{
			const int32 curPixelIndex = ((y * TextureWidth) + x);
			Pixels[4 * curPixelIndex] = B;
			Pixels[4 * curPixelIndex + 1] = G;
			Pixels[4 * curPixelIndex + 2] = R;
			Pixels[4 * curPixelIndex + 3] = A;
		}
	}

	// Allocate first mipmap.
	FTexture2DMipMap* Mip = new(NewTexture->PlatformData->Mips) FTexture2DMipMap();
	Mip->SizeX = TextureWidth;
	Mip->SizeY = TextureHeight;

	// Lock the texture so it can be modified
	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = static_cast<uint8*>(Mip->BulkData.Realloc(TextureWidth * TextureHeight * 4));
	FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * TextureHeight * TextureWidth * 4);
	Mip->BulkData.Unlock();

	NewTexture->Source.Init(TextureWidth, TextureHeight, 1, 1, ETextureSourceFormat::TSF_BGRA8, Pixels);

	NewTexture->UpdateResource();
	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(NewTexture);

	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName,
	                                                                  FPackageName::GetAssetPackageExtension());
	bool bSaved = UPackage::SavePackage(Package, NewTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
	                                    *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	delete[] Pixels; // Don't forget to free the memory here
}
