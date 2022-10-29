// Copyright https://github.com/travmygit. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_RandomSelector.generated.h"

/**
 * Random Selector composite node.
 * Select randomly from child branches to execute.
 * The result of the branch will be the result of the composite.
 */
UCLASS()
class NEXTGENBEHAVIORTREEPLUS_API UBTComposite_RandomSelector : public UBTCompositeNode
{
	GENERATED_BODY()

public:
	UBTComposite_RandomSelector();
	
protected:
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = Composite, meta = (EditCondition = "bUseWeights"))
	TArray<float> Weights;

	UPROPERTY(EditAnywhere, Category = Composite, meta = (InlineEditConditionToggle))
	bool bUseWeights = false;
};
