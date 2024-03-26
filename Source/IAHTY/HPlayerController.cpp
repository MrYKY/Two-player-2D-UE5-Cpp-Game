// Fill out your copyright notice in the Description page of Project Settings.


#include "HPlayerController.h"

#include "HGameModeBase.h"
#include "Blueprint/UserWidget.h"

AHPlayerController::AHPlayerController()
{
}

void AHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Player State
	HPlayerState = Cast<AHPlayerState>(PlayerState);
	// Get Game Mode
	HGameMode = GetWorld()->GetAuthGameMode<AHGameModeBase>();
	
	HGameMode->OnTurnEnd.AddDynamic(this, &AHPlayerController::UpdateHappinessIndex);
	
	// Create the main UI widget
	if (IsLocalController() && MainUIWidgetClass != nullptr)
	{
		// 创建Widget实例
		MainUIWidgetInstance = CreateWidget<UUserWidget>(this, MainUIWidgetClass);

		if (MainUIWidgetInstance != nullptr)
		{
			// 将Widget添加到视口
			MainUIWidgetInstance->AddToViewport();
		}
	}
	bShowMouseCursor = true;

	// 设置输入模式，使玩家可以与UI交互，但不捕获鼠标
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
            
	SetInputMode(InputModeData);
}

void AHPlayerController::TryStartNewRound()
{
	if(HPlayerState; HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done && HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::NotDone;
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::NotDone;
		
		if(HGameMode)
		{
			HGameMode->OnTurnEnd.Broadcast();
		}
	}
}

void AHPlayerController::TryEndGame()
{
	if(HPlayerState->PlayerA.LifeHappinessIndex <= 0 || HPlayerState->PlayerB.LifeHappinessIndex <= 0)
	{
		HGameMode->OnGameEnd.Broadcast();
	}
	if(HGameMode->CurrentRound==MAX_ROUND)
	{
		HGameMode->OnGameEnd.Broadcast();
	}
}

void AHPlayerController::SetPlayerState(EPlayerIndex PlayerIndex, EPlayerTurnState NewState)
{
	
}

void AHPlayerController::UpdateHappinessIndex()
{
	HPlayerState->AddLifeHappinessIndex(&HPlayerState->PlayerA,
		HPlayerState->PlayerA.ShortTermHappinessIndex*HPlayerState->PlayerA.AccumulationRatio);
	HPlayerState->AddLifeHappinessIndex(&HPlayerState->PlayerB,
		HPlayerState->PlayerB.ShortTermHappinessIndex*HPlayerState->PlayerB.AccumulationRatio);
}

void AHPlayerController::AWork()
{
	if(HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A is done this turn.")));
	}
	if(HPlayerState->PlayerA.TurnState == EPlayerTurnState::NotDone)
	{
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA)==EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Work);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A already made choice.")));
		}
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();

}

void AHPlayerController::AStudy()
{
	if(HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A is done this turn.")));
	}
	if(HPlayerState->PlayerA.TurnState == EPlayerTurnState::NotDone)
	{
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA)==EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Study);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A already made choice.")));
		}
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();

}

void AHPlayerController::AConsume()
{
	if(HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A is done this turn.")));
	}
	if(HPlayerState->PlayerA.TurnState == EPlayerTurnState::NotDone)
	{
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA)==EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Consume);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A already made choice.")));
		}
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();

}

void AHPlayerController::BWork()
{
	if(HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B is done this turn.")));
	}
	if(HPlayerState->PlayerB.TurnState == EPlayerTurnState::NotDone)
	{
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerB)==EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Work);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B already made choice.")));
		}
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();

}

void AHPlayerController::BStudy()
{
	if(HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B is done this turn.")));
	}
	if(HPlayerState->PlayerB.TurnState == EPlayerTurnState::NotDone)
	{
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerB)==EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Study);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B already made choice.")));
		}
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();

}

void AHPlayerController::BConsume()
{
	if(HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B is done this turn.")));
	}
	if(HPlayerState->PlayerB.TurnState == EPlayerTurnState::NotDone)
	{
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerB)==EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Consume);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B already made choice.")));
		}
		if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();

}

void AHPlayerController::SettleConditions()
{
	if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA)==EPlayerActionChoice::Work)
	{
		switch (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB))
		{
			case EPlayerActionChoice::Work:
				HPlayerState->AddMoney(&HPlayerState->PlayerA, HPlayerState->PlayerA.WorkingAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -WORKING_HAPPINESS_CUT);

				HPlayerState->AddMoney(&HPlayerState->PlayerB, HPlayerState->PlayerB.WorkingAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -WORKING_HAPPINESS_CUT);
				break;
		
			case EPlayerActionChoice::Study:
				HPlayerState->AddMoney(&HPlayerState->PlayerA, HPlayerState->PlayerA.WorkingAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -WORKING_HAPPINESS_CUT);

				HPlayerState->AddWorkingAbility(&HPlayerState->PlayerB, HPlayerState->PlayerB.LearningAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -LEARNING_HAPPINESS_CUT);
				break;
			case EPlayerActionChoice::Consume:
				HPlayerState->AddMoney(&HPlayerState->PlayerA, HPlayerState->PlayerA.WorkingAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -2 * WORKING_HAPPINESS_CUT);
			
				HPlayerState->AddMoney(&HPlayerState->PlayerB, -BASIC_CONSUME_COST);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, BASIC_CONSUME_HAPPINES_GET);
				break;
				
			default: break;
		}
	}
	if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA)==EPlayerActionChoice::Study)
	{
		switch (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB))
		{
			case EPlayerActionChoice::Work:
				HPlayerState->AddWorkingAbility(&HPlayerState->PlayerA, HPlayerState->PlayerA.LearningAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -LEARNING_HAPPINESS_CUT);

				HPlayerState->AddMoney(&HPlayerState->PlayerB, HPlayerState->PlayerB.WorkingAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -WORKING_HAPPINESS_CUT);
				break;
				
			case EPlayerActionChoice::Study:
				HPlayerState->AddWorkingAbility(&HPlayerState->PlayerA, HPlayerState->PlayerA.LearningAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -LEARNING_HAPPINESS_CUT);
			
				HPlayerState->AddWorkingAbility(&HPlayerState->PlayerB, HPlayerState->PlayerB.LearningAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -LEARNING_HAPPINESS_CUT);
				break;
				
			case EPlayerActionChoice::Consume:
				HPlayerState->AddWorkingAbility(&HPlayerState->PlayerA, HPlayerState->PlayerA.LearningAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -2 * LEARNING_HAPPINESS_CUT);
			
				HPlayerState->AddMoney(&HPlayerState->PlayerB, -BASIC_CONSUME_COST);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, BASIC_CONSUME_HAPPINES_GET);
				break;
				
			default: break;
		}
	}
	if(HPlayerState->GetActionChoice(EPlayerIndex::PlayerA)==EPlayerActionChoice::Consume)
	{
		switch (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB))
		{
			case EPlayerActionChoice::Work:
				HPlayerState->AddMoney(&HPlayerState->PlayerA, -BASIC_CONSUME_COST);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, BASIC_CONSUME_HAPPINES_GET);
			
				HPlayerState->AddMoney(&HPlayerState->PlayerB, HPlayerState->PlayerB.WorkingAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -2 * WORKING_HAPPINESS_CUT);
				break;
				
			case EPlayerActionChoice::Study:
				HPlayerState->AddMoney(&HPlayerState->PlayerA, -BASIC_CONSUME_COST);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, BASIC_CONSUME_HAPPINES_GET);

				HPlayerState->AddWorkingAbility(&HPlayerState->PlayerB, HPlayerState->PlayerB.LearningAbility);
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -2 * LEARNING_HAPPINESS_CUT);
				break;
				
			case EPlayerActionChoice::Consume:
				if(HPlayerState->PlayerA.ShortTermHappinessIndex < HPlayerState->PlayerB.ShortTermHappinessIndex)
				{
					HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -FAIL_TO_CONSUME_PUNISH);
					
					HPlayerState->AddMoney(&HPlayerState->PlayerB, -BASIC_CONSUME_COST);
					HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, BASIC_CONSUME_HAPPINES_GET);
				}
				else if(HPlayerState->PlayerA.ShortTermHappinessIndex > HPlayerState->PlayerB.ShortTermHappinessIndex)
				{
					HPlayerState->AddMoney(&HPlayerState->PlayerA, -BASIC_CONSUME_COST);
					HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, BASIC_CONSUME_HAPPINES_GET);

					HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -FAIL_TO_CONSUME_PUNISH);
				}
				else
				{
					HPlayerState->AddMoney(&HPlayerState->PlayerA, -BASIC_CONSUME_COST/2);
					HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, BASIC_CONSUME_HAPPINES_GET/2);
					
					HPlayerState->AddMoney(&HPlayerState->PlayerB, -BASIC_CONSUME_COST/2);
					HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, BASIC_CONSUME_HAPPINES_GET/2);
				}
				break;
				
			default: break;
		}
	}
	HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Tbd);
	HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Tbd);
}


