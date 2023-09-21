// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "InfantryCharacter.generated.h"


UENUM()
enum InfantrySoldierState
{
	Standing UMETA(DisplayName = "Standing"),
	Prone UMETA(DisplayName = "Prone"),
	LyingFaceDown UMETA(DisplayName = "LyingFaceDown"),
	Agonizing UMETA(DisplayName = "Agonizing"),
	Dead UMETA(DisplayName = "Dead"),
};

UCLASS()
class NEWERABATTLEFIELD_API AInfantryCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AInfantryCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:	

	

	// Camera

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// Soldier State

	//UPROPERTY(EditAnywhere,  Category = "InfantrySoldierState")
	//InfantrySoldierState infantrySoldierState = InfantrySoldierState::Standing;

	// Input

	UPROPERTY(EditAnywhere,  Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InfantryMappingContext;

	UPROPERTY(EditAnywhere,  Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere,  Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;


protected:
	
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

};
