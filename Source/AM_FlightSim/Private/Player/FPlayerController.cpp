// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPlayerController.h"

#include "Player/FPlayerCharacter.h"

void AFPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	PlayerCharacter = Cast<AFPlayerCharacter>(NewPawn);

}

void AFPlayerController::BeginPlay()
{
	Super::BeginPlay();

}
