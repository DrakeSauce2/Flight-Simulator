// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    void LoadMainMenu();
    void LoadMainLevel();

private:
    UPROPERTY(EditAnywhere, Category = "Maps")
    FName MainMenuMapName;

    UPROPERTY(EditAnywhere, Category = "Maps")
    FName MainLevelMapName;

};
