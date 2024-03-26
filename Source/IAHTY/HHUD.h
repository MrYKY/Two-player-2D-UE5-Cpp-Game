// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TSubclassOf<UUserWidget> MainUIWidgetClass;

	// 存储Widget实例的指针
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* MainUIWidgetInstance;

	virtual void BeginPlay() override;
};
