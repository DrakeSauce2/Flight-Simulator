// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"

#include "Framework/FGameInstance.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UMainMenu::NativeConstruct()
{
    LoadLevelButton->OnClicked.AddDynamic(this, &UMainMenu::LoadLevel);
}

void UMainMenu::LoadLevel()
{
    UFGameInstance* GameInstance = Cast<UFGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        GameInstance->LoadMainLevel();
    }
}

