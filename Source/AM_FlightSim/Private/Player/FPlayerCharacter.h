// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FCharacterBase.h"
#include "FPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class AFPlayerCharacter : public AFCharacterBase
{
	GENERATED_BODY()
	
public:
	AFPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(visibleAnywhere, Category = "View")
		USpringArmComponent* cameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
		UCameraComponent* viewCamera;

/*****************************************************/
/*                     Physics                       */
/*****************************************************/

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float StartSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float Mass = 14378.8781f; // In Kilograms; 14378.8781 is the weight of an F-15

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float Gravity = -9.81f;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float EngineThrust = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float MaxVelocity = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float LookInterpRate = 10.f;

	FVector Velocity;

	void CalculateVelocity();

	FVector CalculateWeight();
	FVector CalculateLift();
	float CalculateAoA();

	FVector CalculateThrust();

/*****************************************************/
/*                     Visual                        */
/*****************************************************/

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	class UNiagaraComponent* LeftJetVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	class UNiagaraComponent* RightJetVFX;

/*****************************************************/
/*                       Input                       */
/*****************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* ThrustInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* LurchInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* RollInputAction;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void InputThrottle(const FInputActionValue& InputValue);

	UFUNCTION()
		void Look(const FInputActionValue& InputValue);
	UFUNCTION()
		void ApplyRudder(const FInputActionValue& InputValue);
	UFUNCTION()
		void Roll(const FInputActionValue& InputValue);
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		float RollRate = 15.f;

	float ThrottleValue;
	float Rudder;
	float ThrottleInRate = 1.f;

};
