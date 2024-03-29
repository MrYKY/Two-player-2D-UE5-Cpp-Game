// Fill out your copyright notice in the Description page of Project Settings.


#include "HPlayerController.h"
#include "HGameModeBase.h"

AHPlayerController::AHPlayerController()
{
}
void AHPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Get Player State
	HPlayerState = Cast<AHPlayerState>(PlayerState);
}

void AHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get Game Mode
	HGameMode = GetWorld()->GetAuthGameMode<AHGameModeBase>();
	HGameMode->OnTurnEnd.AddDynamic(this, &AHPlayerController::UpdateHappinessIndex);
	HGameMode->OnGameRestart.AddDynamic(this, &AHPlayerController::RestartGame);
	
	bShowMouseCursor = true;
	// 设置输入模式，使玩家可以与UI交互，但不捕获鼠标
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}


void AHPlayerController::TryStartNewRound()
{
	if (HPlayerState; HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done && HPlayerState->PlayerB.TurnState ==
		EPlayerTurnState::Done)
	{
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::NotDone;
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::NotDone;

		if (HGameMode)
		{
			HGameMode->OnTurnEnd.Broadcast();
		}
	}
}

void AHPlayerController::TryEndGame()
{
	if (HPlayerState->PlayerA.LifeHappinessIndex <= 0 || HPlayerState->PlayerB.LifeHappinessIndex <= 0)
	{
		HGameMode->OnGameEnd.Broadcast();
	}
	if (HGameMode->CurrentRound == MAX_ROUND)
	{
		HGameMode->OnGameEnd.Broadcast();
	}
}

void AHPlayerController::SetPlayerState(EPlayerIndex PlayerIndex, EPlayerTurnState NewState)
{
}

void AHPlayerController::RestartGame()
{
	HPlayerState->Reset();
}

void AHPlayerController::UpdateHappinessIndex()
{
	HPlayerState->AddLifeHappinessIndex(&HPlayerState->PlayerA,
	                                    HPlayerState->PlayerA.ShortTermHappinessIndex * HPlayerState->PlayerA.
	                                    AccumulationRatio);
	HPlayerState->AddLifeHappinessIndex(&HPlayerState->PlayerB,
	                                    HPlayerState->PlayerB.ShortTermHappinessIndex * HPlayerState->PlayerB.
	                                    AccumulationRatio);
}

void AHPlayerController::AWork()
{
	if (HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A is done this turn.")));
	}
	if (HPlayerState->PlayerA.TurnState == EPlayerTurnState::NotDone)
	{
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) == EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Work);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
			                                 FString::Printf(TEXT("Player A already made choice.")));
		}
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();
	TryEndGame();
}

void AHPlayerController::AStudy()
{
	if (HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A is done this turn.")));
	}
	if (HPlayerState->PlayerA.TurnState == EPlayerTurnState::NotDone)
	{
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) == EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Study);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
			                                 FString::Printf(TEXT("Player A already made choice.")));
		}
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();
	TryEndGame();
}

void AHPlayerController::AConsume()
{
	if (HPlayerState->PlayerA.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player A is done this turn.")));
	}
	if (HPlayerState->PlayerA.TurnState == EPlayerTurnState::NotDone)
	{
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) == EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Consume);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
			                                 FString::Printf(TEXT("Player A already made choice.")));
		}
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerA.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();
	TryEndGame();
}

void AHPlayerController::BWork()
{
	if (HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B is done this turn.")));
	}
	if (HPlayerState->PlayerB.TurnState == EPlayerTurnState::NotDone)
	{
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) == EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Work);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
			                                 FString::Printf(TEXT("Player B already made choice.")));
		}
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();
	TryEndGame();
}

void AHPlayerController::BStudy()
{
	if (HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B is done this turn.")));
	}
	if (HPlayerState->PlayerB.TurnState == EPlayerTurnState::NotDone)
	{
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) == EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Study);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
			                                 FString::Printf(TEXT("Player B already made choice.")));
		}
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();
	TryEndGame();
}

void AHPlayerController::BConsume()
{
	if (HPlayerState->PlayerB.TurnState == EPlayerTurnState::Done)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Player B is done this turn.")));
	}
	if (HPlayerState->PlayerB.TurnState == EPlayerTurnState::NotDone)
	{
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB) == EPlayerActionChoice::Tbd)
		{
			HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Consume);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
			                                 FString::Printf(TEXT("Player B already made choice.")));
		}
		if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) != EPlayerActionChoice::Tbd)
		{
			SettleConditions();
		}
		HPlayerState->PlayerB.TurnState = EPlayerTurnState::Done;
	}
	TryStartNewRound();
	TryEndGame();
}

void AHPlayerController::BuyItem(EPlayerIndex PlayerIndex ,FName ItemName)
{
	AHItem* NewItem = NewObject<AHItem>(this, ItemClass);
	NewItem->InitializeItem(ItemName);
	HPlayerState->AddMoney(PlayerIndex,NewItem->ItemBaseInfo.Price);
	HPlayerState->AddItem(PlayerIndex, NewItem);
}

void AHPlayerController::SettleConditions()
{
	if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) == EPlayerActionChoice::Work)
	{
		switch (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB))
		{
		case EPlayerActionChoice::Work:
			HPlayerState->AddMoney(EPlayerIndex::PlayerA, HPlayerState->PlayerA.WorkingAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -WORKING_HAPPINESS_CUT);

			HPlayerState->AddMoney(EPlayerIndex::PlayerB, HPlayerState->PlayerB.WorkingAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -WORKING_HAPPINESS_CUT);
			break;

		case EPlayerActionChoice::Study:
			HPlayerState->AddMoney(EPlayerIndex::PlayerA, HPlayerState->PlayerA.WorkingAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -WORKING_HAPPINESS_CUT);

			HPlayerState->AddWorkingAbility(&HPlayerState->PlayerB, HPlayerState->PlayerB.LearningAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -LEARNING_HAPPINESS_CUT);
			break;
		case EPlayerActionChoice::Consume:
			HPlayerState->AddMoney(EPlayerIndex::PlayerA, HPlayerState->PlayerA.WorkingAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -2 * WORKING_HAPPINESS_CUT);

			BuyItem(EPlayerIndex::PlayerB, "BasicConsume");
			break;

		default: break;
		}
	}
	if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) == EPlayerActionChoice::Study)
	{
		switch (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB))
		{
		case EPlayerActionChoice::Work:
			HPlayerState->AddWorkingAbility(&HPlayerState->PlayerA, HPlayerState->PlayerA.LearningAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -LEARNING_HAPPINESS_CUT);

			HPlayerState->AddMoney(EPlayerIndex::PlayerB, HPlayerState->PlayerB.WorkingAbility);
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

			BuyItem(EPlayerIndex::PlayerB, "BasicConsume");
			break;

		default: break;
		}
	}
	if (HPlayerState->GetActionChoice(EPlayerIndex::PlayerA) == EPlayerActionChoice::Consume)
	{
		switch (HPlayerState->GetActionChoice(EPlayerIndex::PlayerB))
		{
		case EPlayerActionChoice::Work:
			BuyItem(EPlayerIndex::PlayerA, "BasicConsume");

			HPlayerState->AddMoney(EPlayerIndex::PlayerB, HPlayerState->PlayerB.WorkingAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -2 * WORKING_HAPPINESS_CUT);
			break;

		case EPlayerActionChoice::Study:
			BuyItem(EPlayerIndex::PlayerA, "BasicConsume");

			HPlayerState->AddWorkingAbility(&HPlayerState->PlayerB, HPlayerState->PlayerB.LearningAbility);
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -2 * LEARNING_HAPPINESS_CUT);
			break;

		case EPlayerActionChoice::Consume:
			if (HPlayerState->PlayerA.ShortTermHappinessIndex < HPlayerState->PlayerB.ShortTermHappinessIndex)
			{
				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, -FAIL_TO_CONSUME_PUNISH);

				BuyItem(EPlayerIndex::PlayerB, "BasicConsume");
			}
			else if (HPlayerState->PlayerA.ShortTermHappinessIndex > HPlayerState->PlayerB.ShortTermHappinessIndex)
			{
				BuyItem(EPlayerIndex::PlayerA, "BasicConsume");

				HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, -FAIL_TO_CONSUME_PUNISH);
			}
			else
			{
				BuyItem(EPlayerIndex::PlayerA, "BasicConsume");

				BuyItem(EPlayerIndex::PlayerB, "BasicConsume");
			}
			break;

		default: break;
		}
	}
	SettleItemEffects();
	SettleItemUniqueEffects();
	HPlayerState->SetActionChoice(EPlayerIndex::PlayerA, EPlayerActionChoice::Tbd);
	HPlayerState->SetActionChoice(EPlayerIndex::PlayerB, EPlayerActionChoice::Tbd);
}

void AHPlayerController::SettleItemEffects()
{
	for (AHItem* Item : HPlayerState->PlayerA.Items)
	{
		if(Item->HappinessStack.Num()>0)
		{
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerA, Item->HappinessStack.Pop());
		}
		else
		{
			if(!Item->ItemBaseInfo.HasUniqueEffect)
			{
				HPlayerState->PlayerA.Items.Remove(Item);
			}
		}
		
	}
	for (AHItem* Item : HPlayerState->PlayerB.Items)
	{
		if(Item->HappinessStack.Num()>0)
		{
			HPlayerState->AddShortTermHappinessIndex(&HPlayerState->PlayerB, Item->HappinessStack.Pop());
		}
		else
		{
			if(!Item->ItemBaseInfo.HasUniqueEffect)
			{
				HPlayerState->PlayerB.Items.Remove(Item);
			}
		}
		
	}
}

void AHPlayerController::SettleItemUniqueEffects()
{
}
