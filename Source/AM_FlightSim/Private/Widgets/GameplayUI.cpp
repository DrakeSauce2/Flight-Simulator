// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameplayUI.h"

#include "Components/TextBlock.h"

void UGameplayUI::OnCheckpointCountUpdated(int CurrentCount, int MaxCount)
{
	FString DisplayText = FString::Printf(TEXT("Checkpoints: %d / %d"), CurrentCount, MaxCount);
	CheckpointCounterText->SetText(FText::FromString(DisplayText));
}

void UGameplayUI::OnTimerUpdated(float ElapsedTime)
{
    int32 Minutes = FMath::FloorToInt(ElapsedTime / 60.0f);
    int32 Seconds = FMath::FloorToInt(FMath::Fmod(ElapsedTime, 60.0f));

    FString DisplayText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

    CheckpointCounterText->SetText(FText::FromString(DisplayText));
}
