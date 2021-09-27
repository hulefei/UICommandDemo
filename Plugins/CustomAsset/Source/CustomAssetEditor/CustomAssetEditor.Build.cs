using UnrealBuildTool;

public class CustomAssetEditor : ModuleRules
{
	public CustomAssetEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
				"CustomAsset",
				"Kismet",
				"PropertyEditor",
				"BehaviorTreeEditor",
				"ToolMenus",
				"GraphEditor",
			});
		
		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"UnrealEd",
//				"WorkspaceMenuStructure",
			});
	}
}