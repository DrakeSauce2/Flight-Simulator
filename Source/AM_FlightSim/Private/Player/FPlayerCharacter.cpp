// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Math/Vector.h"

#include "NiagaraComponent.h"

AFPlayerCharacter::AFPlayerCharacter()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	viewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");

	cameraBoom->SetupAttachment(GetMesh());
	viewCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = 800.f;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(1080.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
}

void AFPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetCapsuleComponent()) return;

	GetCapsuleComponent()->AddTorqueInDegrees(-GetCapsuleComponent()->GetPhysicsAngularVelocityInDegrees() / 0.75f, NAME_None, true);
	GetCapsuleComponent()->AddForce(FVector(0, 0, -10000.f), NAME_None, true);

	Speed();

	if (ThrottleValue <= 0) 
	{
		currentThrottle = FMath::FInterpConstantTo(currentThrottle, 0, DeltaTime, 10.f);
	}
}

void AFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ThrottleTimer, this, &AFPlayerCharacter::Throttle, 1.f/60.f, true);
}

void AFPlayerCharacter::Throttle()
{
	if (ThrottleValue > 0)
	{
		currentThrottle = FMath::Clamp(currentThrottle + 1.f, 0, MaxThrottle);

		if (currentThrottle > 50.f) 
		{
			//LeftJetVFX->Activate();
			//RightJetVFX->Activate();
		}
	}
	else
	{
		//LeftJetVFX->Deactivate();
		//RightJetVFX->Deactivate();
	}
}

void AFPlayerCharacter::Speed()
{
	FVector ForwardThrust = GetCapsuleComponent()->GetForwardVector() * (currentThrottle * 500.f);
	GetCapsuleComponent()->SetPhysicsLinearVelocity(FMath::VInterpTo(GetCapsuleComponent()->GetPhysicsLinearVelocity(), ForwardThrust, 0.1f, 1.f));
}

void AFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}

	UEnhancedInputComponent* enhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComp)
	{
		enhancedInputComp->BindAction(ThrustInputAction, ETriggerEvent::Triggered, this, &AFPlayerCharacter::InputThrottle);
		enhancedInputComp->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AFPlayerCharacter::Look);
		enhancedInputComp->BindAction(RollInputAction, ETriggerEvent::Triggered, this, &AFPlayerCharacter::Roll);
		enhancedInputComp->BindAction(LurchInputAction, ETriggerEvent::Triggered, this, &AFPlayerCharacter::ApplyRudder);
	}
}

void AFPlayerCharacter::InputThrottle(const FInputActionValue& InputValue)
{
	float input = InputValue.Get<float>() / ThrottleInRate;

	ThrottleValue = FMath::Clamp(ThrottleValue + input, 0, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("Thrust Value: %f"), ThrottleValue);
}

void AFPlayerCharacter::Look(const FInputActionValue& InputValue)
{
	float input = InputValue.Get<float>();

	float YThrottle = currentThrottle > 0 ? input * -2000 : (input * -2000) / 3;
	FVector TargetTorqueY = GetCapsuleComponent()->GetRightVector() * YThrottle;

	GetCapsuleComponent()->AddTorqueInDegrees
	(
		FMath::VInterpTo(FVector::ZeroVector, TargetTorqueY, 0.1f, LookInterpRate),
		NAME_None,
		true
	);
}

void AFPlayerCharacter::ApplyRudder(const FInputActionValue& InputValue)
{
	float input = InputValue.Get<float>();

	Rudder = input * (currentThrottle / MaxThrottle);

	FVector TargetTorque = FMath::VInterpTo
	(
		FVector::ZeroVector,
		GetCapsuleComponent()->GetUpVector() * (Rudder * 1250.f),
		0.1f,
		1.f
	);

	GetCapsuleComponent()->AddTorqueInDegrees(TargetTorque, NAME_None, true);
}

void AFPlayerCharacter::Roll(const FInputActionValue& InputValue)
{
	float input = InputValue.Get<float>();

	float XThrottle = currentThrottle > 0 ? input * -2000 : (input * -2000) / 3;
	FVector TargetTorqueX = GetCapsuleComponent()->GetForwardVector() * XThrottle;

	GetCapsuleComponent()->AddTorqueInDegrees
	(
		FMath::VInterpTo(FVector::ZeroVector, TargetTorqueX, 0.1f, 1.f),
		NAME_None,
		true
	);
	
}
