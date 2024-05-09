// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCheckPointManager.generated.h"

class AFCheckPoint;
UCLASS()
class AFCheckPointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFCheckPointManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Checkpoints")
	TArray<AFCheckPoint*> Checkpoints;

	UFUNCTION()
	void NextCheckPoint();

	void UpdateUI();

	bool CheckHasGUI();

	UPROPERTY()
	class UGameplayUI* GUI;

	int CurrentCheckpoint = 0;

};
