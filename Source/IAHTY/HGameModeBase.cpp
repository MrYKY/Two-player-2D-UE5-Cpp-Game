// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameModeBase.h"

AHGameModeBase::AHGameModeBase()
{
	// Bind the StartNewRound function to the OnTryStartNewRound event
	OnTurnEnd.AddDynamic(this, &AHGameModeBase::StartNewRound);
}

void AHGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHGameModeBase::StartNewRound()
{
	CurrentRound += 1;
}
