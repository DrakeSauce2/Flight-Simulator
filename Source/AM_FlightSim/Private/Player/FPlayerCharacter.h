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
		float TakeoffSpeedThreshold;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float ThrustSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float MaxThrottle = 750.f;

	UPROPERTY(EditDefaultsOnly, Category = "Plane")
		float LookInterpRate = 10.f;

	void Throttle();
	void Speed();

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

	FTimerHandle ThrottleTimer;

		float ThrottleValue = 0;
		float ThrottleInRate = 60.f;
		float currentThrottle = 0;
		float Rudder = 0;

};
