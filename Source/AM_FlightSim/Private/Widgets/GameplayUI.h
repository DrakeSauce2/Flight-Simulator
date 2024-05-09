// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayUI.generated.h"

/**
 * 
 */
UCLASS()
class UGameplayUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void OnCheckpointCountUpdated(int CurrentCount, int MaxCount);
	void OnTimerUpdated(float ElapsedTime);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CheckpointCounterText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText;


};
