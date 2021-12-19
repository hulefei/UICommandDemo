// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ModuleExampleEditor : ModuleRules
{
	public ModuleExampleEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"MainFrame",
//				"WorkspaceMenuStructure",
			});
		
		PrivateIncludePaths.AddRange(
			new string[] {
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"ContentBrowser",
				"Core",
				"CoreUObject",
				"DesktopWidgets",
				"EditorStyle",
				"Engine",
				"InputCore",
				"Projects",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"Kismet",
				"PropertyEditor",
				"BehaviorTreeEditor",
				"ToolMenus",
				"GraphEditor",
				"Sequencer",
				"SequencerWidgets",
				"MovieScene",
				"TimeManagement",
				"ModuleExample"
			});
		
		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"UnrealEd",
//				"WorkspaceMenuStructure",
			});
	}
}