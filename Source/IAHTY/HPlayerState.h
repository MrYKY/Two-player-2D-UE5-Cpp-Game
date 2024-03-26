// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
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
	float LifeHappinessIndex = 0;

	// 短期幸福指数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float ShortTermHappinessIndex = 1000;

	// 积累比率
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float AccumulationRatio = 0.1;

	// 玩家所拥有的金钱
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float Money = 3000;

	// 工作能力
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float WorkingAbility = 0;

	// 学习能力
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats")
	float LearningAbility = 1000;

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
	void AddMoney(FPlayerInfo* Player, float Amount);
	void AddLifeHappinessIndex(FPlayerInfo* Player, float Amount);
	void AddShortTermHappinessIndex(FPlayerInfo* Player, float Amount);
	void AddLearningAbility(FPlayerInfo* Player, float Amount);
	void AddWorkingAbility(FPlayerInfo* Player, float Amount);
	void SetTurnState(FPlayerInfo* Player, EPlayerTurnState NewState);
	void SetActionChoice(EPlayerIndex PlayerIndex, EPlayerActionChoice NewChoice);
	EPlayerActionChoice GetActionChoice(EPlayerIndex PlayerIndex);
	void SetActionChoice(FPlayerInfo* PlayerA, EPlayerActionChoice NewChoice);
	// 其他修改器函数...
	
};
