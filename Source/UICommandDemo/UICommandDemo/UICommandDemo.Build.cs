// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UICommandDemo : ModuleRules
{
	public UICommandDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "KSkillCore", "ModuleExample"});
		
		PrivateDependencyModuleNames.AddRange(new string[] { "ModuleExample" });
	}
}