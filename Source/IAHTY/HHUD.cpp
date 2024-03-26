// Fill out your copyright notice in the Description page of Project Settings.


#include "HHUD.h"
#include "Blueprint/UserWidget.h"


void AHHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HGameMode = Cast<AHGameModeBase>(GetWorld()->GetAuthGameMode());
	if (HGameMode)
	{
		HGameMode->OnGameEnd.AddDynamic(this, &AHHUD::EndGame);
	}
	
}

void AHHUD::BeginPlay()
{
	Super::BeginPlay();
	
	// Create the main UI widget
	if (StartMenuWidgetClass != nullptr)
	{
		APlayerController* PlayerController = GetOwningPlayerController();
		if(PlayerController)
		{
			// 创建Widget实例
			StartMenuWidgetInstance = CreateWidget<UUserWidget>(PlayerController, StartMenuWidgetClass);

			if (StartMenuWidgetInstance != nullptr)
			{
				// 将Widget添加到视口
				StartMenuWidgetInstance->AddToViewport();
			}

			MainUIWidgetInstance = CreateWidget<UUserWidget>(PlayerController, MainUIWidgetClass);
			GameEndWidgetInstance = CreateWidget<UUserWidget>(PlayerController, GameEndWidgetClass);
		}
	}
}



void AHHUD::StartGame()
{
	if (MainUIWidgetInstance != nullptr)
	{
		MainUIWidgetInstance->AddToViewport();
	}
	if (StartMenuWidgetInstance != nullptr)
	{
		StartMenuWidgetInstance->RemoveFromParent();
	}
}

void AHHUD::EndGame()
{
	if (GameEndWidgetInstance != nullptr)
	{
		GameEndWidgetInstance->AddToViewport();
	}
	if (MainUIWidgetInstance != nullptr)
	{
		MainUIWidgetInstance->RemoveFromParent();
	}
}

void AHHUD::ReplayGame()
{
	if (GameEndWidgetInstance != nullptr)
	{
		GameEndWidgetInstance->RemoveFromParent();
	}
	if (StartMenuWidgetInstance != nullptr)
	{
		StartMenuWidgetInstance->AddToViewport();
	}
	HGameMode->OnGameRestart.Broadcast();
}
