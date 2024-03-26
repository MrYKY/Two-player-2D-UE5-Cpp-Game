// Fill out your copyright notice in the Description page of Project Settings.


#include "HPlayerState.h"

void AHPlayerState::AddMoney(FPlayerInfo* Player, float Amount)
{
	Player->Money += Amount;
}

void AHPlayerState::AddLifeHappinessIndex(FPlayerInfo* Player, float Amount)
{
	Player->LifeHappinessIndex += Amount;
}

void AHPlayerState::AddShortTermHappinessIndex(FPlayerInfo* Player, float Amount)
{
	Player->ShortTermHappinessIndex += Amount;
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
