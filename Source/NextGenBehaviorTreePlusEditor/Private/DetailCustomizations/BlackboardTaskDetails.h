// Copyright https://github.com/travmygit. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Layout/Visibility.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class IPropertyUtilities;
class IPropertyHandle;
class UBlackboardData;
class UBlackboardKeyType;

class FBlackboardTaskDetails : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;

private:
	bool IsEditingEnabled() const;
	void CacheBlackboardData(IDetailLayoutBuilder& DetailLayout);
	void OnKeyIDChanged();
	
	EVisibility GetIntValueVisibility() const;
	EVisibility GetFloatValueVisibility() const;
	EVisibility GetStringValueVisibility() const;
	EVisibility GetBoolValueVisibility() const;
	EVisibility GetVectorValueVisibility() const;
	EVisibility GetRotatorValueVisibility() const;
	EVisibility GetNameValueVisibility() const;

private:
	TSharedPtr<IPropertyUtilities> PropUtils;
	TSharedPtr<IPropertyHandle> KeyIDProperty;
	TSubclassOf<UBlackboardKeyType> CachedKeyType;
	TWeakObjectPtr<UBlackboardData> CachedBlackboardAsset;
};
