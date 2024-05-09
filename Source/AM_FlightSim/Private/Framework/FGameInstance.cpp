// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UFGameInstance::LoadMainMenu()
{
    if (!MainMenuMapName.IsNone())
    {
        UWorld* World = GetWorld();
        if (World)
        {
            UGameplayStatics::OpenLevel(World, MainMenuMapName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load map: World is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load map: MapToLoad is not set"));
    }
}

void UFGameInstance::LoadMainLevel()
{
    if (!MainLevelMapName.IsNone())
    {
        UWorld* World = GetWorld();
        if (World)
        {
            UGameplayStatics::OpenLevel(World, MainLevelMapName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load map: World is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load map: MapToLoad is not set"));
    }
}
