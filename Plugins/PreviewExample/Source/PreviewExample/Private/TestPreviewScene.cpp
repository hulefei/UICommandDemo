// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPreviewScene.h"

#include "Editor.h"
#include "Components/PostProcessComponent.h"
#include "Engine/TextureCube.h"
#include "Materials/MaterialInstanceConstant.h"


FTestPreviewScene::FTestPreviewScene(ConstructionValues CVS) : FPreviewScene(CVS)
{
	CreateSkySphere();
	CreateFloor();
	
	// const FTransform Transform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1));
	// //Set Sky Light
	// const FString EnvironmentCubeMapPath = TEXT("/Engine/EditorMaterials/AssetViewer/EpicQuadPanorama_CC+EV1.EpicQuadPanorama_CC+EV1");
	// UObject* LoadedObject = LoadObject<UObject>(nullptr, *EnvironmentCubeMapPath);
	// while (UObjectRedirector* Redirector = Cast<UObjectRedirector>(LoadedObject))
	// {
	// 	LoadedObject = Redirector->DestinationObject;
	// }
	// TSoftObjectPtr<UTextureCube> EnvironmentCubeMap = LoadedObject;
	// SetSkyCubemap(EnvironmentCubeMap.Get());
	// SetSkyBrightness(1.0f);
	// //Set Sky Sphere
	// // Large scale to prevent sphere from clipping
	// const FTransform SphereTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(2000));
	// UStaticMeshComponent* SkyComponent = NewObject<UStaticMeshComponent>(GetTransientPackage());
	//
	// // Set up sky sphere showing hte same cube map as used by the sky light
	// UStaticMesh* SkySphere = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/AssetViewer/Sphere_inversenormals.Sphere_inversenormals"), NULL, LOAD_None, NULL);
	// check(SkySphere);
	// SkyComponent->SetStaticMesh(SkySphere);
	// SkyComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// SkyComponent->bVisibleInRayTracing = false;
	//
	// UMaterial* SkyMaterial = LoadObject<UMaterial>(NULL, TEXT("/Engine/EditorMaterials/AssetViewer/M_SkyBox.M_SkyBox"), NULL, LOAD_None, NULL);
	// check(SkyMaterial);
	//
	// UMaterialInstanceConstant* InstancedSkyMaterial = NewObject<UMaterialInstanceConstant>(GetTransientPackage());
	// InstancedSkyMaterial->Parent = SkyMaterial;
	//
	// UTextureCube* DefaultTexture = LoadObject<UTextureCube>(NULL, TEXT("/Engine/MapTemplates/Sky/SunsetAmbientCubemap.SunsetAmbientCubemap"));
	//
	// // InstancedSkyMaterial->SetTextureParameterValueEditorOnly(FName("SkyBox"), (EnvironmentCubeMap.Get() != nullptr) ? EnvironmentCubeMap.Get() : DefaultTexture);
	// InstancedSkyMaterial->SetScalarParameterValueEditorOnly(FName("CubemapRotation"), 0);
	// InstancedSkyMaterial->SetScalarParameterValueEditorOnly(FName("Intensity"), 1.0f);
	// InstancedSkyMaterial->PostLoad();
	// SkyComponent->SetMaterial(0, InstancedSkyMaterial);
	// AddComponent(SkyComponent, SphereTransform);
	//
	// UPostProcessComponent* PostProcessComponent = NewObject<UPostProcessComponent>();
	// PostProcessComponent->bUnbound = true;
	// AddComponent(PostProcessComponent, Transform);
	//
	// //TODO set floor Y
	// UStaticMesh* FloorMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh"), NULL, LOAD_None, NULL);
	// check(FloorMesh);
	// UStaticMeshComponent* FloorMeshComponent = NewObject<UStaticMeshComponent>(GetTransientPackage());
	// FloorMeshComponent->SetStaticMesh(FloorMesh);
	//
	// FTransform FloorTransform(FRotator(0, 0, 0), FVector(0, 0, -(0.0f)), FVector(4.0f, 4.0f, 1.0f));
	// AddComponent(FloorMeshComponent, FloorTransform);
	// FloorMeshComponent->SetVisibility(false);
	//
	// // since advance preview scenes are used in conjunction with material/mesh editors we should match their feature level with the global one
	// if (GIsEditor && GEditor != nullptr)
	// {
	// 	PreviewWorld->ChangeFeatureLevel(GEditor->DefaultWorldFeatureLevel);
	// }
}

void FTestPreviewScene::CreateSkySphere()
{
	// create a sky sphere
	UStaticMeshComponent* SkyComp = NewObject<UStaticMeshComponent>();
	UStaticMesh * StaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/MapTemplates/Sky/SM_SkySphere.SM_SkySphere"), NULL, LOAD_None, NULL);
	SkyComp->SetStaticMesh(StaticMesh);
	UMaterial* SkyMaterial = LoadObject<UMaterial>(NULL, TEXT("/Engine/EditorMaterials/PersonaSky.PersonaSky"), NULL, LOAD_None, NULL);
	SkyComp->SetMaterial(0, SkyMaterial);
	const float SkySphereScale = 1000.f;
	const FTransform SkyTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(SkySphereScale));
	AddComponent(SkyComp, SkyTransform);
}

void FTestPreviewScene::CreateFloor()
{
	// now add floor
	UStaticMesh* FloorMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/EditorCube.EditorCube"), NULL, LOAD_None, NULL);
	UStaticMeshComponent* FloorComp = NewObject<UStaticMeshComponent>();
	FloorComp->SetStaticMesh(FloorMesh);
	const FTransform FloorTransform(FRotator(0, 0, 0), FVector(0, 0, -(0.0f)), FVector(4.0f, 4.0f, 1.0f));
	AddComponent(FloorComp, FloorTransform);
	FloorComp->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));
	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Engine/EditorMaterials/PersonaFloorMat.PersonaFloorMat"), NULL, LOAD_None, NULL);
	FloorComp->SetMaterial(0, Material);
	FloorComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FloorComp->SetCollisionObjectType(ECC_WorldStatic);
}


