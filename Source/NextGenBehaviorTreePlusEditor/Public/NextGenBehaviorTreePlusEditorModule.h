// Copyright https://github.com/travmygit. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FNextGenBehaviorTreePlusEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
