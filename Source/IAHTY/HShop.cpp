// Fill out your copyright notice in the Description page of Project Settings.


#include "HShop.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameStateBase.h"


// Sets default values
AHShop::AHShop()
{
}

// Called when the game starts or when spawned
void AHShop::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BeginePlay"));
	HPlayerState = Cast<AHPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	HPlayerController = Cast<AHPlayerController>(GetWorld()->GetFirstPlayerController());
	if(!HPlayerController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerControllerNotFound"));
	}
	HPlayerController->OnShopperChanged.AddDynamic(this, &AHShop::UpdateShopper);
	HPlayerController->OnShopEntered.AddDynamic(this, &AHShop::EnterShop);
	
}

// Called every frame
void AHShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHShop::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



void AHShop::UpdateShopper()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ShopperChanged"));
	if(HPlayerState->PlayerA.ActionChoice == EPlayerActionChoice::Consume &&
		HPlayerState->PlayerB.ActionChoice != EPlayerActionChoice::Consume)
	{
		ShopperIndex = EPlayerIndex::PlayerA;
		ShopperNum = 1;
	}
	else if(HPlayerState->PlayerA.ActionChoice != EPlayerActionChoice::Consume &&
		HPlayerState->PlayerB.ActionChoice == EPlayerActionChoice::Consume)
	{
		ShopperIndex = EPlayerIndex::PlayerB;
		ShopperNum = 1;
	}
	else if(HPlayerState->PlayerA.ActionChoice == EPlayerActionChoice::Consume &&
		HPlayerState->PlayerB.ActionChoice == EPlayerActionChoice::Consume)
	{
		if(HPlayerState->PlayerA.ShortTermHappinessIndex > HPlayerState->PlayerB.ShortTermHappinessIndex)
		{
			ShopperIndex = EPlayerIndex::PlayerA;
		}
		else if(HPlayerState->PlayerA.ShortTermHappinessIndex < HPlayerState->PlayerB.ShortTermHappinessIndex)
		{
			ShopperIndex = EPlayerIndex::PlayerB;
		}
		else
		{
			int32 Rand = FMath::RandRange(0, 1);
			if(Rand == 0)
			{
				ShopperIndex = EPlayerIndex::PlayerA;
			}
			else
			{
				ShopperIndex = EPlayerIndex::PlayerB;
			}
		}
		ShopperNum = 2;
	}
	else
	{
		ShopperNum = 0;
		ShouldExitShop = true;
		ShopWidgetInstance->RemoveFromParent();
		HPlayerController->OnShopExited.Broadcast();
		Destroy();
	}
}

void AHShop::EnterShop()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnterShop"));
	ShopWidgetInstance = CreateWidget<UUserWidget>(HPlayerController, ShopWidgetClass);
	ShopWidgetInstance->AddToViewport();
}


