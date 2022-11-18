// Copyright https://github.com/travmygit. All Rights Reserved.

#include "NextGenBehaviorTreePlusEditorModule.h"
#include "DetailCustomizations/BlackboardTaskDetails.h"

#define LOCTEXT_NAMESPACE "FNextGenBehaviorTreePlusEditorModule"

void FNextGenBehaviorTreePlusEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// Register the details customizer
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("BTTask_Blackboard", FOnGetDetailCustomizationInstance::CreateStatic( &FBlackboardTaskDetails::MakeInstance ));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FNextGenBehaviorTreePlusEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Unregister the details customization
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("BTTask_Blackboard");
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNextGenBehaviorTreePlusEditorModule, NextGenBehaviorTreePlusEditor)