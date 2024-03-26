// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameModeBase.h"


AHGameModeBase::AHGameModeBase()
{
	OnTurnEnd.AddDynamic(this, &AHGameModeBase::StartNewRound);
	OnGameEnd.AddDynamic(this,&AHGameModeBase::EndGame);
	OnGameRestart.AddDynamic(this, &AHGameModeBase::RestartGame);
}

void AHGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHGameModeBase::StartNewRound()
{
	CurrentRound += 1;
}

void AHGameModeBase::EndGame()
{
}

void AHGameModeBase::RestartGame()
{
	CurrentRound = 1;
}
