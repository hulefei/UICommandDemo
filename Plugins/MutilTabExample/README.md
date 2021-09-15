# 总结

### 示意流程

0. FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MutilTabExampleTabName, OnSpawnPluginTab)
1. FGlobalTabmanager.RegisterNomadTabSpawner(InnerTabName, SDockTab)
2. FGlobalTabmanager.RegisterNomadTabSpawner(InnerTabName2, SDockTab)
3. OnSpawnPluginTab 
    0. NomadTab = SNew(SDockTab)
    1. TabManager = FGlobalTabmanager.NewTabManager
    2. TabManagerLayout.AddArea(FTabManager.NewPrimaryArea)
        .Split(FTabManager::NewStack)
        .Split(FTabManager::NewStack)
    3. TabContents = TabManager.RestoreFrom
    4. NomadTab.SetContent(TabContents)
4. FGlobalTabmanager::Get()->TryInvokeTab(MutilTabExampleTabName);


[原文](https://www.codenong.com/cs109321869/)