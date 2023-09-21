// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstPersonPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NewEraBattlefield/Characters_F/FirstPersonCharacter.h"

AFirstPersonPlayerController::AFirstPersonPlayerController()
{
}

AFirstPersonPlayerController::~AFirstPersonPlayerController()
{
}

void AFirstPersonPlayerController::SetupInputMapping() const
{
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}


void AFirstPersonPlayerController::SetupPlayerReference()
{
	FirstPersonCharacter = Cast<AFirstPersonCharacter>(GetPawn());
	
	if(!FirstPersonCharacter)
		UE_LOG(LogFPSController, Error, TEXT("Couldn't find the player Pawn!"));
}

void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetupPlayerReference();
	SetupInputMapping();
}

void AFirstPersonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	Input->BindAction(Move_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleMove);
	Input->BindAction(Look_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleLook);
	Input->BindAction(Aim_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleAim);
	Input->BindAction(Shoot_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleShoot);
	Input->BindAction(PickItem_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandlePickUpItem);
	Input->BindAction(Jump_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleJump);
	Input->BindAction(Reload_InputAction, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleReload);
}


void AFirstPersonPlayerController::HandleMove(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;
	const FVector2D& Movement = Value.Get<FVector2D>();
	FirstPersonCharacter->Move(Movement);
}

void AFirstPersonPlayerController::HandleLook(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;
	const FVector2D& Look = Value.Get<FVector2D>();
	FirstPersonCharacter->Look(Look);
}

void AFirstPersonPlayerController::HandleAim(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;

	FirstPersonCharacter->Aim();
}

void AFirstPersonPlayerController::HandleShoot(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;

	FirstPersonCharacter->Shoot();
}

void AFirstPersonPlayerController::HandlePickUpItem(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;

	FirstPersonCharacter->PickUp();
}

void AFirstPersonPlayerController::HandleJump(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;
	FirstPersonCharacter->Jump();
}

void AFirstPersonPlayerController::HandleReload(const FInputActionValue& Value)
{
	if(!FirstPersonCharacter)
		return;

	FirstPersonCharacter->Reload();
}