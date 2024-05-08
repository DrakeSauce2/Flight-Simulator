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

FVector AFPlayerCharacter::CalculateVerticleForce()
{
	// Lift = LiftCoefficient * Density * VelocityOfAir^2 / 2 * WingArea
	// Lift = AoA * (1/2Density) * Speed * WingArea
	float AngleOfAttack = FVector::DotProduct(GetCapsuleComponent()->GetForwardVector(), FVector(1.f, 0, 0));
	AngleOfAttack = FMath::RadiansToDegrees(AngleOfAttack);
	float AirDensity = 1.204f; // kg/m
	Lift = AngleOfAttack * (AirDensity/2) * Velocity * 56.5f;

	UE_LOG(LogTemp, Warning, TEXT("AoA: %f"), AngleOfAttack);

	Weight = Mass * Gravity;
	return Lift + FVector(0, 0, Weight);
}

FVector AFPlayerCharacter::CalculateDrag()
{
	FVector DragForce = DragCoefficient * (Velocity.SizeSquared() / 2.f) * Velocity.GetSafeNormal();
	return  DragForce;
}

void AFPlayerCharacter::CalculateVelocity()
{
	Velocity += CalculateVerticleForce() + CalculateDrag() + CalculateThrust();
	if (Velocity.SizeSquared() > TerminalVelocity * TerminalVelocity)
	{
		Velocity = Velocity.GetSafeNormal() * TerminalVelocity;
	}

	GetCapsuleComponent()->AddForce(CalculateVerticleForce());
	GetCapsuleComponent()->AddForce(CalculateDrag());
	GetCapsuleComponent()->AddForce(CalculateThrust());
	//GetCapsuleComponent()->AddForce(Velocity);
} 

FVector AFPlayerCharacter::CalculateThrust()
{
	FVector ThrustForce = GetCapsuleComponent()->GetForwardVector() * ((EngineThrust * ThrottleValue) / Mass);
	return ThrustForce;
}

void AFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Velocity = GetCapsuleComponent()->GetForwardVector() * StartSpeed;

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

	//float YThrottle = currentThrottle > 0 ? input.Y * -2000 : (input.Y * -2000) / 25.F;
	FVector TargetTorqueY = GetCapsuleComponent()->GetRightVector() * -2000 * input.Y;

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
