// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEditorViewportClient.h"
#include "TestPreviewScene.h"
#include "STestEditorViewport.h"

FTestEditorViewportClient::FTestEditorViewportClient(FEditorModeTools* InModeTools, FTestPreviewScene* InPreviewScene,
                                                     const TWeakPtr<STestEditorViewport>& InEditorViewportWidget) :
	FEditorViewportClient(InModeTools, InPreviewScene, InEditorViewportWidget)
{

	TestPreviewScene = InPreviewScene;
	TestEditorViewport = InEditorViewportWidget;

	check(TestPreviewScene)
	
	SetRealtime(true);

	const FVector DefaultPerspectiveViewLocation( 200.f, 1000.f, 300.f );
	const FRotator DefaultPerspectiveViewRotation( -17.f, -100.0f, 0 );
	
	//Initiate view
	SetViewLocation(DefaultPerspectiveViewLocation);
	SetViewRotation(DefaultPerspectiveViewRotation);
	
	AddStaticCube();
}

FTestEditorViewportClient::~FTestEditorViewportClient()
{
}

void FTestEditorViewportClient::AddStaticCube()
{
	//向预览场景中加一个测试模型
		//读取模型
		UStaticMesh* SM = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"), NULL, LOAD_None, NULL);
		//创建组件
		UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>();
		SMC->SetStaticMesh(SM);
		//向预览场景中增加组件
		TestPreviewScene->AddComponent(SMC, FTransform::Identity);
}

void FTestEditorViewportClient::Tick(float DeltaSeconds)
{
	// UE_LOG(LogTemp, Log, TEXT("Location:%s"), *GetViewLocation().ToString());
	// UE_LOG(LogTemp, Log, TEXT("Rotator:%s"), *GetViewRotation().ToString());
	
	FEditorViewportClient::Tick(DeltaSeconds);
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}
