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

	CalculateVelocity();
}

FVector AFPlayerCharacter::CalculateWeight()
{
	FVector Weight = FVector::DownVector * Mass * Gravity;
	return Weight;
}

void AFPlayerCharacter::CalculateVelocity()
{
	Velocity += CalculateThrust() + CalculateWeight() + CalculateLift();

	if (Velocity.SizeSquared() > MaxVelocity * MaxVelocity)
	{
		Velocity = Velocity.GetSafeNormal() * MaxVelocity;
	}
	
	GetCapsuleComponent()->SetAllPhysicsLinearVelocity(Velocity, false);

	UE_LOG(LogTemp, Warning, TEXT("Velocity Magnitude: %f"), Velocity.Size());
} 

FVector AFPlayerCharacter::CalculateThrust()
{
	FVector ThrustForce = GetCapsuleComponent()->GetForwardVector() * ((EngineThrust * ThrottleValue) / 2);

	return ThrustForce;
}

FVector AFPlayerCharacter::CalculateLift()
{
	// Couldn't figure out how to properly apply lift without Bernouli's principle. So this is just a cheat solution.
	FVector Lift = FVector::UpVector* Gravity* FMath::Cos(CalculateAoA()); 

	return Lift;
}

float AFPlayerCharacter::CalculateAoA()
{
	// Calculate the angle between the velocity vector and the longitudinal axis of the airplane
	float AngleOfAttack = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetCapsuleComponent()->GetForwardVector(), FVector::UpVector)));

	return AngleOfAttack - 90;
}

void AFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Velocity = FVector::ZeroVector;

	ThrottleValue = 0.7f;
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
	FVector2D input = InputValue.Get<FVector2D>();

	float PitchRate = input.Y >= 0 ? -50.f : -25.f;
	FVector TargetTorqueY = GetCapsuleComponent()->GetRightVector() * PitchRate * input.Y;

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

	//Rudder = input * (currentThrottle / MaxThrottle);
	Rudder = input;

	FVector TargetTorque = FMath::VInterpTo
	(
		FVector::ZeroVector,
		GetCapsuleComponent()->GetUpVector() * (Rudder * 450.f),
		0.1f,
		1.f
	);

	GetCapsuleComponent()->AddTorqueInDegrees(TargetTorque, NAME_None, true);
	
}

void AFPlayerCharacter::Roll(const FInputActionValue& InputValue)
{
	float input = InputValue.Get<float>();

	FVector TargetTorqueX = GetCapsuleComponent()->GetForwardVector() * -2000 * input;

	GetCapsuleComponent()->AddTorqueInDegrees
	(
		FMath::VInterpTo(FVector::ZeroVector, TargetTorqueX, 0.1f, 1.f),
		NAME_None,
		true
	);
}
