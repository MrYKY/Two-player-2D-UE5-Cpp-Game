// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HPlayerController.h"
#include "HPlayerState.h"
#include "GameFramework/Actor.h"
#include "HShop.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopperUpdatedDelegate);

UCLASS()
class IAHTY_API AHShop : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHShop();

	UPROPERTY(BlueprintReadOnly, Category = "Player State")
	AHPlayerState* HPlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Player State")
	AHPlayerController* HPlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> ShopWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* ShopWidgetInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	EPlayerIndex ShopperIndex;
	
	bool ShouldExitShop = false;
	bool IsBasicConsumableBought = false;
	
	int32 ShopperNum = 0;
	
	virtual void PostInitializeComponents() override;
	

	UFUNCTION(BlueprintCallable)
	void UpdateShopper();

	UFUNCTION(BlueprintCallable)
	void EnterShop();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
