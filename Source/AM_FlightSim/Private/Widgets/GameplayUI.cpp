// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameplayUI.h"

#include "Components/TextBlock.h"

void UGameplayUI::OnCheckpointCountUpdated(int CurrentCount, int MaxCount)
{
	FString DisplayText = FString::Printf(TEXT("Checkpoints: %d / %d"), CurrentCount, MaxCount);
	CheckpointCounterText->SetText(FText::FromString(DisplayText));
}

