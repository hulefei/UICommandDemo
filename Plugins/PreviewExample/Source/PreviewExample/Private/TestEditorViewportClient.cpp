// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEditorViewportClient.h"
#include "TestPreviewScene.h"
#include "STestEditorViewport.h"
#include "Animation/AnimInstance.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "AnimPreviewInstance.h"
#include "GameFramework/Character.h"

FTestEditorViewportClient::FTestEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene,
                                                     const TWeakPtr<STestEditorViewport>& InEditorViewportWidget) :
	FEditorViewportClient(InModeTools, InPreviewScene, InEditorViewportWidget)
{
	TestPreviewScene = static_cast<FTestPreviewScene*>(InPreviewScene);
	TestEditorViewport = InEditorViewportWidget;

	check(TestPreviewScene)

	UDebugSkelMeshComponent* PreviewMeshComponent = TestPreviewScene->GetPreviewMeshComponent();
	check(PreviewMeshComponent)
	UAnimPreviewInstance* PreviewInstance = PreviewMeshComponent->PreviewInstance;
	check(PreviewInstance)
	
	SetRealtime(true);

	const FVector DefaultPerspectiveViewLocation(200.f, 1000.f, 300.f);
	const FRotator DefaultPerspectiveViewRotation(-17.f, -100.0f, 0);

	//Initiate view
	SetViewLocation(DefaultPerspectiveViewLocation);
	SetViewRotation(DefaultPerspectiveViewRotation);

	UAnimMontage* AnimMontage = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/FightingAnimsetPro/Montages/Skill1.Skill1'"));
	PreviewInstance->SetAnimationAsset(AnimMontage);
	
	// AddStaticCube();
	// AddStaticBlueprint();
	// PlayAnim();

	// Montage = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/FightingAnimsetPro/Montages/Skill1.Skill1'"));
	// PreviewInstance->Montage_Play(Montage);
	
}

FTestEditorViewportClient::~FTestEditorViewportClient()
{
}

void FTestEditorViewportClient::AddStaticCube()
{
	//向预览场景中加一个测试模型
	//读取模型
	UStaticMesh* SM = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"), NULL, LOAD_None,
	                                          NULL);
	//创建组件
	UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>();
	SMC->SetStaticMesh(SM);
	//向预览场景中增加组件
	TestPreviewScene->AddComponent(SMC, FTransform::Identity);
}


void FTestEditorViewportClient::AddStaticBlueprint()
{
	FTransform EmptyTransform;
	UBlueprint* Blueprint = LoadObject<UBlueprint>(
		nullptr, TEXT("Blueprint'/Game/FightingThirdPersonCharacter.FightingThirdPersonCharacter'"));
	const AActor* SpawnActor = Cast<AActor>(Blueprint->GeneratedClass->GetDefaultObject());
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Name = MakeUniqueObjectName(PreviewScene->GetWorld(), SpawnActor->GetClass());
	ActorSpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ActorSpawnParameters.ObjectFlags = EObjectFlags::RF_Transient;
	MainActor = Cast<ACharacter>(
		PreviewScene->GetWorld()->SpawnActor(SpawnActor->GetClass(), &EmptyTransform, ActorSpawnParameters));
}

// void FTestEditorViewportClient::PlayAnim()
// {
// 	UAnimMontage* AnimMontage = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/FightingAnimsetPro/Montages/Skill1.Skill1'"));
// 	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(
// 		MainActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
// 	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
// 	AnimInstance->Montage_Play(AnimMontage);
// }

void FTestEditorViewportClient::ForwardMontage()
{
	if (UAnimSingleNodeInstance* PreviewInstance = GetPreviewInstance())
	{
		bool bShouldStepCloth = FMath::Abs(PreviewInstance->GetLength() - PreviewInstance->GetCurrentTime()) > SMALL_NUMBER;

		PreviewInstance->SetPlaying(false);
		PreviewInstance->StepForward();

		// if(SMC && bShouldStepCloth)
		// {
		// 	SMC->bPerformSingleClothingTick = true;
		// }
	}
}

void FTestEditorViewportClient::PlayMontage()
{
	UAnimSingleNodeInstance* PreviewInstance = GetPreviewInstance();
	check(PreviewInstance)
	if (PreviewInstance != nullptr)
	{
		bool bShouldStepCloth = FMath::Abs(PreviewInstance->GetLength() - PreviewInstance->GetCurrentTime()) > SMALL_NUMBER;
		PreviewInstance->SetReverse(false);
		PreviewInstance->SetPlaying(true);
		UE_LOG(LogTemp, Log, TEXT("PreviewInstance not nullptr"));
	} else
	{
		UE_LOG(LogTemp, Log, TEXT("PreviewInstance is nullptr"));
	}
}

UAnimSingleNodeInstance* FTestEditorViewportClient::GetPreviewInstance() const
{
	UDebugSkelMeshComponent* PreviewMeshComponent = TestPreviewScene->GetPreviewMeshComponent();
	return PreviewMeshComponent && PreviewMeshComponent->IsPreviewOn()? PreviewMeshComponent->PreviewInstance : nullptr;
}

void FTestEditorViewportClient::ReverseAnim()
{
	UAnimMontage* AnimMontage = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/FightingAnimsetPro/Montages/Skill1.Skill1'"));
	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(
		MainActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	AnimInstance->Montage_Play(AnimMontage);
}

void FTestEditorViewportClient::StopMontage()
{
	// USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(
	// 	MainActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	// UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	// AnimInstance->Montage_Stop(0.25f);
	UAnimSingleNodeInstance* PreviewInstance = GetPreviewInstance();
	check(PreviewInstance)
	if (PreviewInstance != nullptr)
	{
		PreviewInstance->SetPlaying(false);
	}
}

void FTestEditorViewportClient::AddStaticSkeletalMesh()
{
	
}

void FTestEditorViewportClient::Tick(float DeltaSeconds)
{
	// UE_LOG(LogTemp, Log, TEXT("Location:%s"), *GetViewLocation().ToString());
	// UE_LOG(LogTemp, Log, TEXT("Rotator:%s"), *GetViewRotation().ToString());

	FEditorViewportClient::Tick(DeltaSeconds);
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}
