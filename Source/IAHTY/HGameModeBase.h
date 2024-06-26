// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGameModeBase.generated.h"

/**
 *
 */

// Constants
#define BASIC_CONSUME_COST 1000
#define LEARNING_HAPPINESS_CUT 100
#define WORKING_HAPPINESS_CUT 200
#define BASIC_CONSUME_HAPPINES_GET 500
#define FAIL_TO_CONSUME_PUNISH 500
#define MAX_ROUND 50
// Initial values
#define INIT_MONEY 3000
#define INIT_LIFE_HAPPINESS_INDEX 100
#define INIT_SHORT_TERM_HAPPINESS_INDEX 1000
#define INIT_ACCUMULATION_RATIO 0.1
#define INIT_WORKING_ABILITY 0
#define INIT_LEARNING_ABILITY 1000

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameRetartDelegate);

UCLASS()
class IAHTY_API AHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable, Category="Game")
	FOnTurnEndDelegate OnTurnEnd;

	UPROPERTY(BlueprintAssignable, Category="Game")
	FOnGameEndDelegate OnGameEnd;

	UPROPERTY(BlueprintAssignable, Category="Game")
	FOnGameRetartDelegate OnGameRestart;
	
	// 当前回合数 CurrentRound
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game State")
	int32 CurrentRound = 1;

	// 最大回合数 MaxRounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game State")
	int32 MaxRounds = MAX_ROUND;
	

	// Constructor
	AHGameModeBase();

	UFUNCTION()
	void StartNewRound();
	
	UFUNCTION()
	void EndGame();
	
	UFUNCTION()
	void RestartGame();


	// 初始化游戏的状态 
	virtual void BeginPlay() override;
	
};
