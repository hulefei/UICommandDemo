#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "AssetTools/CustomAssetActions.h"
#include "DetailCustomizations/CustomAssetCustomization.h"
#include "Modules/ModuleInterface.h"
#include "Templates/SharedPointer.h"
#include "Modules/ModuleManager.h"
#include "Styles/CustomAssetEditorStyle.h"
#include "DetailCustomizations/CustomAssetView.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

class FCustomAssetEditorModule
// : public IHasMenuExtensibility
// , public IHasToolBarExtensibility
 : public IModuleInterface
{
	virtual void StartupModule() override
	{
		Style = MakeShareable(new FCustomAssetEditorStyle());
		RegisterAssetTools();

		// FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		// PropertyModule.RegisterCustomPropertyTypeLayout("CustomAsset", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCustomAssetView::MakeInstance));
		// PropertyModule.NotifyCustomizationModuleChanged();
		auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout(
			UCustomAsset::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FCustomAssetCustomization::MakeInstance)
		);
	}
	virtual void ShutdownModule() override
	{
		UnregisterAssetTools();
	}
	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}
protected:

	/** Registers asset tool actions. */
	void RegisterAssetTools()
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		RegisterAssetTypeAction(AssetTools, MakeShareable(new FCustomAssetActions(Style.ToSharedRef())));
	}

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		RegisteredAssetTypeActions.Add(Action);
	}

	void UnregisterAssetTools()
	{
		FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	
		if (AssetToolsModule != nullptr)
		{
			IAssetTools& AssetTools = AssetToolsModule->Get();
	
			for (auto Action : RegisteredAssetTypeActions)
			{
				AssetTools.UnregisterAssetTypeActions(Action);
			}
		}
	}
	
private:
	// /** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

	/** Holds the plug-ins style set. */
	TSharedPtr<ISlateStyle> Style;
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor);
