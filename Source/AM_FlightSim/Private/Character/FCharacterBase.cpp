// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FCharacterBase.h"

// Sets default values
AFCharacterBase::AFCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

