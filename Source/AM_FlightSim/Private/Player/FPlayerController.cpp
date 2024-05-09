// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPlayerController.h"

#include "Player/FPlayerCharacter.h"
#include "Widgets/GameplayUI.h"


void AFPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	PlayerCharacter = Cast<AFPlayerCharacter>(NewPawn);

	SpawnGameplayUI();
}

void AFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPlayerController::SpawnGameplayUI()
{
	if (!PlayerCharacter)
	{
		return;
	}

	if (!GameplayUIClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s,  missing Gameplay UI class, Can't Spawn Gameplay UI"), *GetName());
		return;
	}

	GameplayUI = CreateWidget<UGameplayUI>(this, GameplayUIClass);
	if (GameplayUI)
	{
		GameplayUI->AddToViewport();
	}
}
