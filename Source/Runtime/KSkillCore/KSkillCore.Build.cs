// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KSkillCore : ModuleRules
{
	public KSkillCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
				// "Runtime/KSkillCore/Public",
				// "Runtime/KSkillCore/Classes"
			}
		);
		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
				// "Runtime/KSkillCore/Private",
			}
		);
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				// "ModuleExampleEditor",
				// ... add private dependencies that you statically link with here ...    
			}
		);
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}