// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HGameModeBase.h"
#include "HPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "HPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class IAHTY_API AHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainUIWidgetClass;

	// 存储Widget实例的指针
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* MainUIWidgetInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Player State")
	AHPlayerState* HPlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode")
	AHGameModeBase* HGameMode;
	
	AHPlayerController();
	virtual void BeginPlay() override;
	void TryStartNewRound();
	void TryEndGame();

	UFUNCTION(BlueprintCallable, Category = "Player State")
	void UpdateHappinessIndex();

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void AWork();
	
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void AStudy();
	
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void AConsume();
	
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void BWork();
	
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void BStudy();
	
	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void BConsume();

	void SettleConditions();
	void SetPlayerState(EPlayerIndex PlayerIndex, EPlayerTurnState NewState);
	
};
