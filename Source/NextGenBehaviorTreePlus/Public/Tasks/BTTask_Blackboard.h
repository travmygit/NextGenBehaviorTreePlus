// Copyright https://github.com/travmygit. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Blackboard.generated.h"

class FBlackboardTaskDetails;
class UBehaviorTree;
class UBlackboardComponent;

/**
 * Blackboard task node.
 * A task node that set blackboard key by its type.
 */
UCLASS()
class NEXTGENBEHAVIORTREEPLUS_API UBTTask_Blackboard : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

protected:

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	int32 IntValue = 0;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	float FloatValue = 0.f;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	FVector VectorValue;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	FRotator RotatorValue;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	FName NameValue;
	
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	FString StringValue;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (DisplayName = "Key Value"))
	bool BoolValue = false;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	friend FBlackboardTaskDetails;
};
