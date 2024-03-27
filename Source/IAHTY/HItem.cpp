// Fill out your copyright notice in the Description page of Project Settings.


#include "HItem.h"

void AHItem::InitializeItem(const FName ItemId)
{
	const UDataTable *ItemDataTable = ItemDataTableClass.GetDefaultObject();
	if (ItemDataTable != nullptr)
	{
		const FHItemInfo* Info = ItemDataTable->FindRow<FHItemInfo>(ItemId, TEXT(""));
		if (Info != nullptr)
		{
			ItemBaseInfo = *Info;
			CalculateHappinessStack();
		}
	}
}

void AHItem::CalculateHappinessStack()
{
	int32 HappinessDecreasePerRound = ItemBaseInfo.STHappinessIncrease/ItemBaseInfo.DecreaseRoundNum;
	HappinessStack.Empty();
	for (int32 i = 0; i < ItemBaseInfo.DecreaseRoundNum; i++)
	{
		HappinessStack.Push(- HappinessDecreasePerRound);
	}
	HappinessStack.Push(ItemBaseInfo.STHappinessIncrease);
}
