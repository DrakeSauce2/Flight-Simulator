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

private:
	UPROPERTY(visibleAnywhere, Category = "View")
		USpringArmComponent* cameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
		UCameraComponent* viewCamera;

	virtual void PawnClientRestart() override;

/*****************************************************/
/*                       Input                       */
/*****************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* ThrustInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* LookInputAction;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void ApplyThrust(const FInputActionValue& InputValue);

	UFUNCTION()
		void Look(const FInputActionValue& InputValue);

	UPROPERTY()
		float ThrustValue = 0;

};
