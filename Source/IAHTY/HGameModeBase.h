// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGameModeBase.generated.h"

/**
 * 
 */

#define BASIC_CONSUME_COST 100
#define LEARNING_HAPPINESS_CUT 200
#define WORKING_HAPPINESS_CUT 500
#define BASIC_CONSUME_HAPPINES_GET 500
#define FAIL_TO_CONSUME_PUNISH 500
#define MAX_ROUND 50

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEndDelegate);

UCLASS()
class IAHTY_API AHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	// Constructor
	AHGameModeBase();
	
	UFUNCTION(BlueprintCallable, Category="Game")
	void StartNewRound();
	
	UFUNCTION(BlueprintCallable, Category="Game")
	void EndGame();

	UPROPERTY(BlueprintAssignable, Category="Game")
	FOnTurnEndDelegate OnTurnEnd;

	UPROPERTY(BlueprintAssignable, Category="Game")
	FOnGameEndDelegate OnGameEnd;
	
	// 当前回合数 CurrentRound
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game State")
	int32 CurrentRound = 1;

	// 最大回合数 MaxRounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game State")
	int32 MaxRounds = MAX_ROUND;

	// 初始化游戏的状态 
	virtual void BeginPlay() override;
	
};
