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

class AHShop;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopperChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopEnteredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopExitedDelegate);

UCLASS()
class IAHTY_API AHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	

	UPROPERTY(BlueprintReadOnly, Category = "Player State")
	AHPlayerState* HPlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode")
	AHGameModeBase* HGameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Info")
	TSubclassOf<AHItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Info")
	TSubclassOf<AHShop> ShopClass;
	
	
	UPROPERTY(BlueprintAssignable, Category="Shop")
	FOnShopperChangedDelegate OnShopperChanged;

	UPROPERTY(BlueprintAssignable, Category="Shop")
	FOnShopEnteredDelegate OnShopEntered;

	UPROPERTY(BlueprintAssignable, Category="Shop")
	FOnShopExitedDelegate OnShopExited;

	bool IsInShop = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Item Info")
	TObjectPtr<AHShop> Shop = nullptr;
	
	
	AHPlayerController();
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	void TryEndTurn();
	void StartNewTurn();
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

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void BuyItem(EPlayerIndex PlayerIndex, FName ItemName);

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void BuyBasicItem(EPlayerIndex PlayerIndex);
	
	UFUNCTION()
	void RestartGame();



	UFUNCTION()
	void ExitShop();
	
	void EnterShop();
	void SettleConditions();
	void SettleItemEffects();
	void SettleItemUniqueEffects();
	void SetPlayerState(EPlayerIndex PlayerIndex, EPlayerTurnState NewState);

};
