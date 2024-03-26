// Fill out your copyright notice in the Description page of Project Settings.


#include "HHUD.h"

#include "Blueprint/UserWidget.h"

void AHHUD::BeginPlay()
{
	Super::BeginPlay();
	
	
	// Create the main UI widget
	if (MainUIWidgetClass != nullptr)
	{
		APlayerController* PlayerController = GetOwningPlayerController();
		if(PlayerController)
		{
			// 创建Widget实例
			MainUIWidgetInstance = CreateWidget<UUserWidget>(PlayerController, MainUIWidgetClass);

			if (MainUIWidgetInstance != nullptr)
			{
				// 将Widget添加到视口
				MainUIWidgetInstance->AddToViewport();
			}
		}
	}
}
