// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AFPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* NewPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	UGameplayUI* GetGUI() { return GameplayUI; }

private:
	void SpawnGameplayUI();

	UPROPERTY()
		class AFPlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UGameplayUI> GameplayUIClass;

	UPROPERTY()
		UGameplayUI* GameplayUI;

};
