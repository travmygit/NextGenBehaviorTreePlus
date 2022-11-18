// Copyright https://github.com/travmygit. All Rights Reserved.

#include "Tasks/BTTask_Blackboard.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_Blackboard::UBTTask_Blackboard(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set Value";
	bNotifyTick = false;
	bNotifyTaskFinished = false;
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
	BlackboardKey.AddNameFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
	BlackboardKey.AddRotatorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
	BlackboardKey.AddStringFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Blackboard, BlackboardKey));
}

EBTNodeResult::Type UBTTask_Blackboard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp && BlackboardKey.SelectedKeyType)
	{
		if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Bool::StaticClass()))
		{
			BlackboardComp->SetValueAsBool(BlackboardKey.SelectedKeyName, BoolValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Float::StaticClass()))
		{
			BlackboardComp->SetValueAsFloat(BlackboardKey.SelectedKeyName, FloatValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Int::StaticClass()))
		{
			BlackboardComp->SetValueAsInt(BlackboardKey.SelectedKeyName, IntValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Name::StaticClass()))
		{
			BlackboardComp->SetValueAsName(BlackboardKey.SelectedKeyName, NameValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Rotator::StaticClass()))
		{
			BlackboardComp->SetValueAsRotator(BlackboardKey.SelectedKeyName, RotatorValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_String::StaticClass()))
		{
			BlackboardComp->SetValueAsString(BlackboardKey.SelectedKeyName, StringValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Vector::StaticClass()))
		{
			BlackboardComp->SetValueAsVector(BlackboardKey.SelectedKeyName, VectorValue);
		}
		else
		{
			return EBTNodeResult::Failed;
		}
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

void UBTTask_Blackboard::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FString DescKeyValue;

	if (BlackboardComp)
	{
		DescKeyValue = BlackboardComp->DescribeKeyValue(BlackboardKey.GetSelectedKeyID(), EBlackboardDescription::KeyWithValue);
	}

	Values.Add(DescKeyValue);
}

FString UBTTask_Blackboard::GetStaticDescription() const
{
	FString DescKeyValue;
	
	if (BlackboardKey.SelectedKeyType)
	{
		if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Bool::StaticClass()))
		{
			DescKeyValue += BoolValue ? TEXT("true") : TEXT("false");
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Float::StaticClass()))
		{
			DescKeyValue += FString::Printf(TEXT("%f"), FloatValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Int::StaticClass()))
		{
			DescKeyValue += FString::Printf(TEXT("%d"), IntValue);
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Name::StaticClass()))
		{
			DescKeyValue += NameValue.ToString();
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Rotator::StaticClass()))
		{
			DescKeyValue += RotatorValue.ToString();
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_String::StaticClass()))
		{
			DescKeyValue += StringValue;
		}
		else if (BlackboardKey.SelectedKeyType->IsChildOf(UBlackboardKeyType_Vector::StaticClass()))
		{
			DescKeyValue += VectorValue.ToString();
		}
		else
		{
			DescKeyValue = TEXT("invalid");
		}
	}
	
	return FString::Printf(TEXT("%s = %s"), *BlackboardKey.SelectedKeyName.ToString(), *DescKeyValue);
}

#if WITH_EDITOR

void UBTTask_Blackboard::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif	// WITH_EDITOR
