// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HGameModeBase.h"
#include "GameFramework/HUD.h"
#include "HHUD.generated.h"

/**
 * 
 */
UCLASS()
class IAHTY_API AHHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> StartMenuWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* StartMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainUIWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* MainUIWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameEndWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* GameEndWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> ShopWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* ShopWidgetInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode")
	AHGameModeBase* HGameMode;

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ReplayGame();

	
};
