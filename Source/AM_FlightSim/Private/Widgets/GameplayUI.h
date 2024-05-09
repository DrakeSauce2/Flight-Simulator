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

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CheckpointCounterText;

};
