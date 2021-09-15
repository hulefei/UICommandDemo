* FUICommandList
    * 存储命令所对应的操作
* TCommands
    * 一组命令 
* FUICommandInfo
    * 对应一种命令 
* FCustomStyle
    * 定义风格
* FUIAction
    * 对应了一个实际的操作 

![image](./Documents/1.png)

### 流程
0. TCommands.Register
    1. TCommands(ContextName, StyleName)
    2. TCommands.RegisterCommands
1. new FUICommandList
2. FUICommandList.MapAction(Command, Action)
3. FModuleManager::LoadModuleChecked<FLevelEditorModule>
    1. new FExtender
    2. MenuExtender.AddMenuExtension(CoommandList, FUICommandInfo)
    2. LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender)
3. FCustomStyle.Initialize
    1. Create
    2. FSlateStyleRegistry::RegisterSlateStyle
4. FTestStyle.ReloadTextures

[原文](https://blog.csdn.net/u013412391/article/details/107891152)