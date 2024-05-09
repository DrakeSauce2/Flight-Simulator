// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FCheckPointManager.h"

#include "Framework/FCheckPoint.h"

#include "Player/FPlayerController.h"

#include "Widgets/GameplayUI.h"

// Sets default values
AFCheckPointManager::AFCheckPointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFCheckPointManager::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentCheckpoint = 0;

	for (AFCheckPoint* checkpoint : Checkpoints)
	{
		checkpoint->CheckpointVisibility(false);
		checkpoint->OnPlayerOverlap.AddUObject(this, &AFCheckPointManager::NextCheckPoint);
	}

	Checkpoints[CurrentCheckpoint]->CheckpointVisibility(true);

	UpdateUI();
}

void AFCheckPointManager::NextCheckPoint()
{
	Checkpoints[CurrentCheckpoint]->CheckpointVisibility(false);
	CurrentCheckpoint++;

	UpdateUI();

	if (CurrentCheckpoint < Checkpoints.Num()) 
	{
		Checkpoints[CurrentCheckpoint]->CheckpointVisibility(true);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("End Of Checkpoints!"));
		// All Checkpoints reached, Display Win Screen
	}

}

void AFCheckPointManager::UpdateUI()
{
	if (CheckHasGUI()) 
	{
		GUI->OnCheckpointCountUpdated(CurrentCheckpoint, Checkpoints.Num());
	}
}

bool AFCheckPointManager::CheckHasGUI()
{
	if (GUI)
	{
		return true;
	}

	AFPlayerController* PlayerController = Cast<AFPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		return false;
	}

	GUI = PlayerController->GetGUI();
	if (!GUI)
	{
		return false;
	}

	UpdateUI();
	return true;
}


