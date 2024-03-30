// Fill out your copyright notice in the Description page of Project Settings.


#include "HPlayerState.h"

void AHPlayerState::AddMoney(EPlayerIndex Player, float Amount)
{
	if(Player == EPlayerIndex::PlayerA)
	{
		PlayerA.Money += Amount;
	}
	if(Player == EPlayerIndex::PlayerB)
	{
		PlayerB.Money += Amount;
	}
}

void AHPlayerState::AddLifeHappinessIndex(FPlayerInfo* Player, float Amount)
{
	Player->LifeHappinessIndex += Amount;
}

void AHPlayerState::AddShortTermHappinessIndex(EPlayerIndex PlayerIndex, float Amount)
{
	if(PlayerIndex == EPlayerIndex::PlayerA)
	{
		PlayerA.ShortTermHappinessIndex += Amount;
	}
	if(PlayerIndex == EPlayerIndex::PlayerB)
	{
		PlayerB.ShortTermHappinessIndex += Amount;
	}
}

void AHPlayerState::AddLearningAbility(FPlayerInfo* Player, float Amount)
{
	Player->LearningAbility += Amount;
}

void AHPlayerState::AddWorkingAbility(FPlayerInfo* Player, float Amount)
{
	Player->WorkingAbility += Amount;
}

void AHPlayerState::SetTurnState(FPlayerInfo* Player, EPlayerTurnState NewState)
{
	Player->TurnState = NewState;
}

void AHPlayerState::SetActionChoice(EPlayerIndex PlayerIndex, EPlayerActionChoice NewChoice)
{
	if(PlayerIndex == EPlayerIndex::PlayerA)
	{
		PlayerA.ActionChoice = NewChoice;
	}
	if(PlayerIndex == EPlayerIndex::PlayerB)
	{
		PlayerB.ActionChoice = NewChoice;
	}
}

EPlayerActionChoice AHPlayerState::GetActionChoice(EPlayerIndex PlayerIndex)
{
	if(PlayerIndex == EPlayerIndex::PlayerA)
	{
		return PlayerA.ActionChoice;
	}
	if(PlayerIndex == EPlayerIndex::PlayerB)
	{
		return PlayerB.ActionChoice;
	}
	return EPlayerActionChoice::Tbd;
}

void AHPlayerState::Reset()
{
	Super::Reset();
	
	PlayerA.Money = INIT_MONEY;
	PlayerA.LifeHappinessIndex = INIT_LIFE_HAPPINESS_INDEX;
	PlayerA.ShortTermHappinessIndex = INIT_SHORT_TERM_HAPPINESS_INDEX;
	PlayerA.WorkingAbility = INIT_WORKING_ABILITY;
	PlayerA.LearningAbility = INIT_LEARNING_ABILITY;
	PlayerA.TurnState = EPlayerTurnState::NotDone;
	PlayerA.ActionChoice = EPlayerActionChoice::Tbd;
	PlayerA.Items.Empty();
	
	PlayerB.Money = INIT_MONEY;
	PlayerB.LifeHappinessIndex = INIT_LIFE_HAPPINESS_INDEX;
	PlayerB.ShortTermHappinessIndex = INIT_SHORT_TERM_HAPPINESS_INDEX;
	PlayerB.WorkingAbility = INIT_WORKING_ABILITY;
	PlayerB.LearningAbility = INIT_LEARNING_ABILITY;
	PlayerB.TurnState = EPlayerTurnState::NotDone;
	PlayerB.ActionChoice = EPlayerActionChoice::Tbd;
	PlayerB.Items.Empty();
	
}

void AHPlayerState::AddItem(EPlayerIndex Player, AHItem* Item)
{
	if(Player == EPlayerIndex::PlayerA)
	{
		PlayerA.Items.Add(Item);
	}
	if(Player == EPlayerIndex::PlayerB)
	{
		PlayerB.Items.Add(Item);
	}
}

void AHPlayerState::SetPlayerState(EPlayerIndex PlayerIndex, EPlayerTurnState NewState)
{
	if(PlayerIndex == EPlayerIndex::PlayerA)
	{
		PlayerA.TurnState = NewState;
	}
	if(PlayerIndex == EPlayerIndex::PlayerB)
	{
		PlayerB.TurnState = NewState;
	}
}


