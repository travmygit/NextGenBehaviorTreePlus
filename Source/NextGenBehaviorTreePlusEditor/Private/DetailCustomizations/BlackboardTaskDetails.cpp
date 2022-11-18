// Copyright https://github.com/travmygit. All Rights Reserved.

#include "DetailCustomizations/BlackboardTaskDetails.h"
#include "Misc/Attribute.h"
#include "SlateOptMacros.h"
#include "BehaviorTree/BTNode.h"
#include "DetailLayoutBuilder.h"
#include "IDetailPropertyRow.h"
#include "DetailCategoryBuilder.h"
#include "IPropertyUtilities.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Tasks/BTTask_Blackboard.h"

#define LOCTEXT_NAMESPACE "BlackboardDecoratorDetails"

TSharedRef<IDetailCustomization> FBlackboardTaskDetails::MakeInstance()
{
	return MakeShareable( new FBlackboardTaskDetails );
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FBlackboardTaskDetails::CustomizeDetails( IDetailLayoutBuilder& DetailLayout )
{
	CacheBlackboardData(DetailLayout);

	IDetailCategoryBuilder& BBCategory = DetailLayout.EditCategory( "Blackboard" );
	IDetailPropertyRow& KeySelectorRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey)));
	KeySelectorRow.IsEnabled(CachedBlackboardAsset.IsValid());

	KeyIDProperty = DetailLayout.GetProperty(FName(TEXT("BlackboardKey.SelectedKeyID")), UBTTask_BlackboardBase::StaticClass());
	if (KeyIDProperty.IsValid())
	{
		KeyIDProperty->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FBlackboardTaskDetails::OnKeyIDChanged));
		OnKeyIDChanged();
	}

	PropUtils = DetailLayout.GetPropertyUtilities();
	TAttribute<bool> PropertyEditCheck = TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateSP(this, &FBlackboardTaskDetails::IsEditingEnabled));

	IDetailPropertyRow& BoolValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BoolValue)));
	BoolValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetBoolValueVisibility)));
	BoolValueRow.IsEnabled(PropertyEditCheck);
	
	IDetailPropertyRow& IntValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, IntValue)));
	IntValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetIntValueVisibility)));
	IntValueRow.IsEnabled(PropertyEditCheck);

	IDetailPropertyRow& FloatValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, FloatValue)));
	FloatValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetFloatValueVisibility)));
	FloatValueRow.IsEnabled(PropertyEditCheck);

	IDetailPropertyRow& NameValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, NameValue)));
	NameValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetNameValueVisibility)));
	NameValueRow.IsEnabled(PropertyEditCheck);

	IDetailPropertyRow& RotatorValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, RotatorValue)));
	RotatorValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetRotatorValueVisibility)));
	RotatorValueRow.IsEnabled(PropertyEditCheck);

	IDetailPropertyRow& VectorValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, VectorValue)));
	VectorValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetVectorValueVisibility)));
	VectorValueRow.IsEnabled(PropertyEditCheck);
	
	IDetailPropertyRow& StringValueRow = BBCategory.AddProperty(DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, StringValue)));
	StringValueRow.Visibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateSP(this, &FBlackboardTaskDetails::GetStringValueVisibility)));
	StringValueRow.IsEnabled(PropertyEditCheck);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

bool FBlackboardTaskDetails::IsEditingEnabled() const
{
	return PropUtils->IsPropertyEditingEnabled();
}

void FBlackboardTaskDetails::CacheBlackboardData(IDetailLayoutBuilder& DetailLayout)
{
	TArray<TWeakObjectPtr<UObject> > MyOuters;
	DetailLayout.GetObjectsBeingCustomized(MyOuters);

	CachedBlackboardAsset.Reset();
	for (int32 i = 0; i < MyOuters.Num(); i++)
	{
		UBTNode* NodeOb = Cast<UBTNode>(MyOuters[i].Get());
		if (NodeOb)
		{
			CachedBlackboardAsset = NodeOb->GetBlackboardAsset();
			break;
		}
	}
}

void FBlackboardTaskDetails::OnKeyIDChanged()
{
	CachedKeyType = nullptr;
	if (CachedBlackboardAsset.IsValid())
	{
		uint8 KeyID;
		FPropertyAccess::Result Result = KeyIDProperty->GetValue(KeyID);
		if (Result == FPropertyAccess::Success)
		{
			const FBlackboardEntry* KeyEntry = CachedBlackboardAsset->GetKey(KeyID);
			if(KeyEntry && KeyEntry->KeyType)
			{
				CachedKeyType = KeyEntry->KeyType->GetClass();
			}
		}
	}
}

EVisibility FBlackboardTaskDetails::GetIntValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_Int::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FBlackboardTaskDetails::GetFloatValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_Float::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FBlackboardTaskDetails::GetStringValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_String::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FBlackboardTaskDetails::GetBoolValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_Bool::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FBlackboardTaskDetails::GetVectorValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_Vector::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FBlackboardTaskDetails::GetRotatorValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_Rotator::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FBlackboardTaskDetails::GetNameValueVisibility() const
{
	return (CachedKeyType == UBlackboardKeyType_Name::StaticClass()) ? EVisibility::Visible : EVisibility::Collapsed;
}

#undef LOCTEXT_NAMESPACE
