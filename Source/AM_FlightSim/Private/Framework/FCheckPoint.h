// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCheckPoint.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

DECLARE_MULTICAST_DELEGATE(FOnPlayerOverlap)

UCLASS()
class AFCheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFCheckPoint();

	FOnPlayerOverlap OnPlayerOverlap;

	void CheckpointVisibility(bool state);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(visibleAnywhere, Category = "View")
	UBoxComponent* TriggerBox;
	
	UPROPERTY(visibleAnywhere, Category = "View")
	UStaticMeshComponent* CheckpointMesh;


};
