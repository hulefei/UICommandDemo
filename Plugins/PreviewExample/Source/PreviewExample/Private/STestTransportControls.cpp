// Fill out your copyright notice in the Description page of Project Settings.


#include "STestTransportControls.h"

#include "EditorWidgetsModule.h"
#include "SlateOptMacros.h"
#include "TestEditorViewportClient.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STestTransportControls::Construct(const FArguments& InArgs)
{
	FEditorWidgetsModule& EditorWidgetsModule = FModuleManager::LoadModuleChecked<FEditorWidgetsModule>("EditorWidgets");
	FTransportControlArgs TransportControlArgs;
	TransportControlArgs.OnForwardPlay = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Forward);
	TransportControlArgs.OnRecord = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Record);
	TransportControlArgs.OnBackwardPlay = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Backward);
	TransportControlArgs.OnForwardStep = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Forward_Step);
	TransportControlArgs.OnBackwardStep = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Backward_Step);
	TransportControlArgs.OnForwardEnd = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Forward_End);
	TransportControlArgs.OnBackwardEnd = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_Backward_End);
	TransportControlArgs.OnToggleLooping = FOnClicked::CreateSP(this, &STestTransportControls::OnClick_ToggleLoop);
	TransportControlArgs.OnGetLooping = FOnGetLooping::CreateSP(this, &STestTransportControls::IsLoopStatusOn);
	TransportControlArgs.OnGetPlaybackMode = FOnGetPlaybackMode::CreateSP(this, &STestTransportControls::GetPlaybackMode);
	TransportControlArgs.OnGetRecording = FOnGetRecording::CreateSP(this, &STestTransportControls::IsRecording);

	TransportControl = EditorWidgetsModule.CreateTransportControl(TransportControlArgs);
	
	ChildSlot
	[
		TransportControl.ToSharedRef()
	];
}

FVector2D STestTransportControls::ComputeDesiredSize(float Scale) const
{
	// auto Size = TransportControl->GetDesiredSize();
	// UE_LOG(LogTemp, Log, TEXT("Size:%f,%f"), Size.X, Size.Y);
	return TransportControl->GetDesiredSize();
	// return FVector2D(100.0f, 35.0f);
}

void STestTransportControls::SetTestEditorViewportClient(TSharedPtr<FTestEditorViewportClient> InTestEditorViewportClient)
{
	TestEditorViewportClient = InTestEditorViewportClient;
	check(TestEditorViewportClient)
}

FReply STestTransportControls::OnClick_Forward_Step()
{
	UE_LOG(LogTemp, Log, TEXT("OnClick_Forward_Step"));
	if (!TestEditorViewportClient.IsValid()) return FReply::Handled();
	TestEditorViewportClient->ForwardMontage();
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_Forward_End()
{
	UE_LOG(LogTemp, Log, TEXT("OnClick_Forward_End"));
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_Backward_Step()
{
	UE_LOG(LogTemp, Log, TEXT("OnClick_Backward_Step"));
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_Backward_End()
{
	UE_LOG(LogTemp, Log, TEXT("OnClick_Backward_End"));
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_Forward()
{
	UE_LOG(LogTemp, Log, TEXT("OnClick_Forward"));
	if (!TestEditorViewportClient.IsValid()) return FReply::Handled();

	if (PlaybackMode == EPlaybackMode::Stopped)
	{
		TestEditorViewportClient->PlayMontage();
		PlaybackMode = EPlaybackMode::PlayingForward;
		// TestEditorViewportClient->PlayAnim();
	} else
	{
		PlaybackMode = EPlaybackMode::Stopped;
		TestEditorViewportClient->StopMontage();
	}
	
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_Backward()
{
	UE_LOG(LogTemp, Log, TEXT("OnClick_Backward"));
	if (!TestEditorViewportClient.IsValid()) return FReply::Handled();

	if (PlaybackMode == EPlaybackMode::Stopped)
	{
		PlaybackMode = EPlaybackMode::PlayingReverse;
		TestEditorViewportClient->ReverseAnim();
	} else
	{
		PlaybackMode = EPlaybackMode::Stopped;
		TestEditorViewportClient->StopMontage();
	}
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_ToggleLoop()
{
	bLoop = !bLoop;
	return FReply::Handled();
}

FReply STestTransportControls::OnClick_Record()
{
	return FReply::Handled();
}

bool STestTransportControls::IsLoopStatusOn() const
{
	return bLoop;
}

EPlaybackMode::Type STestTransportControls::GetPlaybackMode() const
{
	return PlaybackMode;
}

bool STestTransportControls::IsRecording() const
{
	return false;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
