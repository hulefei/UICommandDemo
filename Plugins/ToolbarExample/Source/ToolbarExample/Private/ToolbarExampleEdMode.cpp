// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolbarExampleEdMode.h"
#include "ToolbarExampleEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FToolbarExampleEdMode::EM_ToolbarExampleEdModeId = TEXT("EM_ToolbarExampleEdMode");

FToolbarExampleEdMode::FToolbarExampleEdMode()
{

}

FToolbarExampleEdMode::~FToolbarExampleEdMode()
{

}

void FToolbarExampleEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FToolbarExampleEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FToolbarExampleEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FToolbarExampleEdMode::UsesToolkits() const
{
	return true;
}




