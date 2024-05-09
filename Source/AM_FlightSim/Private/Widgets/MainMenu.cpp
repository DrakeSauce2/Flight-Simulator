// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h" // Include the GameplayStatics header file


void UMainMenu::NativeConstruct()
{
    LoadLevelButton->OnClicked.AddDynamic(this, &UMainMenu::LoadLevel);
}

void UMainMenu::LoadLevel()
{
    // Load the level synchronously
    UWorld* LoadedLevel = GameLevel.LoadSynchronous();
    if (LoadedLevel)
    {
        UGameplayStatics::OpenLevel(GetWorld(), LoadedLevel->GetOuter()->GetFName(), true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load level: GameLevel is null"));
    }
}
