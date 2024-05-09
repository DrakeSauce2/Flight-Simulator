// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FCheckPoint.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Player/FPlayerCharacter.h"

// Sets default values
AFCheckPoint::AFCheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;

    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checkpoint Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFCheckPoint::OnOverlapBegin);

    TriggerBox->SetupAttachment(GetRootComponent());
    CheckpointMesh->SetupAttachment(TriggerBox);
}

void AFCheckPoint::CheckpointVisibility(bool state)
{
    SetActorEnableCollision(state);
    CheckpointMesh->SetVisibility(state);
}

// Called when the game starts or when spawned
void AFCheckPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AFCheckPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const AFPlayerCharacter* Player = Cast<AFPlayerCharacter>(OtherActor);
    if (Player)
    {
        OnPlayerOverlap.Broadcast();
    }
}


