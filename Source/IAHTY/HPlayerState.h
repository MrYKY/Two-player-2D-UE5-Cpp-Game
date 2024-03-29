// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HItem.h"
#include "GameFramework/PlayerState.h"
#include "HGameModeBase.h"
#include "HPlayerState.generated.h"



UENUM(BlueprintType)
enum class EPlayerIndex : uint8
{
	PlayerA UMETA(DisplayName = "Player A"),
	PlayerB UMETA(DisplayName = "Player B"),
};

UENUM(BlueprintType)
enum class EPlayerTurnState : uint8
{
	NotDone UMETA(DisplayName = "Player Not Done Yet"),
	Done UMETA(DisplayName = "Player Done"),
};

UENUM(BlueprintType)
enum class EPlayerActionChoice : uint8
{
	Study UMETA(DisplayName = "Player Chose to Study"),
	Consume UMETA(DisplayName = "Player Chose to Consume"),
	Work UMETA(DisplayName = "Player Chose to Work"),
	Tbd UMETA(DisplayName = "Player Choice TBD"),
};

// 玩家状态数据以及初始值设定
USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
	
	// 生活幸福指数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float LifeHappinessIndex = INIT_LIFE_HAPPINESS_INDEX;

	// 短期幸福指数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float ShortTermHappinessIndex = INIT_SHORT_TERM_HAPPINESS_INDEX;

	// 积累比率
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float AccumulationRatio = INIT_ACCUMULATION_RATIO;

	// 玩家所拥有的金钱
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float Money = INIT_MONEY;

	// 工作能力
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float WorkingAbility = INIT_WORKING_ABILITY;

	// 学习能力
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float LearningAbility = INIT_LEARNING_ABILITY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	TArray<AHItem*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	EPlayerTurnState TurnState = EPlayerTurnState::NotDone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	EPlayerActionChoice ActionChoice = EPlayerActionChoice::Tbd;
	
};

UCLASS()
class IAHTY_API AHPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Info")
	FPlayerInfo PlayerA;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Info")
	FPlayerInfo PlayerB;
	
	
	// 可以添加函数来修改上述属性，例如：
	void AddMoney(EPlayerIndex Player, float Amount);
	void AddLifeHappinessIndex(FPlayerInfo* Player, float Amount);
	void AddShortTermHappinessIndex(FPlayerInfo* Player, float Amount);
	void AddLearningAbility(FPlayerInfo* Player, float Amount);
	void AddWorkingAbility(FPlayerInfo* Player, float Amount);
	void SetTurnState(FPlayerInfo* Player, EPlayerTurnState NewState);
	void SetActionChoice(EPlayerIndex PlayerIndex, EPlayerActionChoice NewChoice);
	EPlayerActionChoice GetActionChoice(EPlayerIndex PlayerIndex);
	void Reset() override;
	void AddItem(EPlayerIndex Player, AHItem* Item);
	void SetPlayerState(EPlayerIndex PlayerIndex, EPlayerTurnState NewState);
	// 其他修改器函数...
	
};
