// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameModeBase.h"

#include "Blueprint/UserWidget.h"

AHGameModeBase::AHGameModeBase()
{
	// Bind the StartNewRound function to the OnTryStartNewRound event
	OnTurnEnd.AddDynamic(this, &AHGameModeBase::StartNewRound);
	OnGameEnd.AddDynamic(this,&AHGameModeBase::EndGame);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
		FString::Printf(TEXT("Game Over!")));
	GameEndWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameEndWidget);
	GameEndWidgetInstance->AddToViewport();
	
}
