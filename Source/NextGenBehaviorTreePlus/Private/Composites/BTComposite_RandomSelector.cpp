// Copyright https://github.com/travmygit. All Rights Reserved.


#include "Composites/BTComposite_RandomSelector.h"

UBTComposite_RandomSelector::UBTComposite_RandomSelector()
{
	NodeName = "Random Selector";
}

int32 UBTComposite_RandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	// success = quit
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		// newly activated: select randomly from children
		const int32 NumChildren = GetChildrenNum();

		if (bUseWeights && ensure(NumChildren == Weights.Num()))
		{
			float TotalWeight = 0.f;
			for (int32 Idx = 0; Idx < NumChildren; ++Idx)
			{
				TotalWeight += Weights[Idx];
			}

			float Rand = FMath::RandRange(0.f, TotalWeight);
			TotalWeight = 0.f;
			for (int32 Idx = 0; Idx < NumChildren; ++Idx)
			{
				TotalWeight += Weights[Idx];
				if (Rand < TotalWeight)
				{
					NextChildIdx = Idx;
					break;
				}
			}
		}
		else
		{
			NextChildIdx = FMath::RandHelper(NumChildren);
		}
	}

	return NextChildIdx;
}

#if WITH_EDITOR

FName UBTComposite_RandomSelector::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Composite.Selector.Icon");
}

void UBTComposite_RandomSelector::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (bUseWeights)
	{
		auto OldValues = Weights;
		const int32 NumChildren = GetChildrenNum();
		Weights.SetNumZeroed(NumChildren);
		for (int32 Idx = 0; Idx < NumChildren; ++Idx)
		{
			if (OldValues.IsValidIndex(Idx))
			{
				Weights[Idx] = OldValues[Idx];
			}
			Weights[Idx] = FMath::Max(1.f, Weights[Idx]);
		}
	}
	else
	{
		Weights.Reset();
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif
