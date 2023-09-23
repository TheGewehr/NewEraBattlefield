// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstPersonPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "NewEraBattlefield/Characters/FirstPersonCharacter.h"
#include "NewEraBattlefield/Components/FirstPersonHealthComponent.h"
#include "NewEraBattlefield/UI/FirstPersonHUDWidget.h"

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

	if(MainHUDWidget && FirstPersonCharacter)
		MainHUDWidget->PlayerOwner = FirstPersonCharacter;
}

void AFirstPersonPlayerController::SetupHUD()
{
	if(MainHUDClass)
	{
		MainHUDWidget = CreateWidget<UFirstPersonHUDWidget>(this, MainHUDClass);
		MainHUDWidget->AddToViewport();
	}
}

void AFirstPersonPlayerController::CreateBindings()
{
	if(!FirstPersonCharacter)
		return;
	FirstPersonCharacter->OnWeaponFireDelegate.AddUObject(this, &AFirstPersonPlayerController::OnWeaponFire);
	FirstPersonCharacter->OnWeaponReloadDelegate.AddUObject(this, &AFirstPersonPlayerController::OnWeaponReload);
	FirstPersonCharacter->OnWeaponChangedDelegate.AddUObject(this, &AFirstPersonPlayerController::OnWeaponChange);
	FirstPersonCharacter->HealthComponent->OnHealthChanged.AddUObject(this, &AFirstPersonPlayerController::OnHealthChange);
}

void AFirstPersonPlayerController::RemoveBindings()
{
	if(!FirstPersonCharacter)
		return;
	FirstPersonCharacter->OnWeaponFireDelegate.RemoveAll(this);
	FirstPersonCharacter->OnWeaponReloadDelegate.RemoveAll(this);
	FirstPersonCharacter->OnWeaponChangedDelegate.RemoveAll(this);
	FirstPersonCharacter->HealthComponent->OnHealthChanged.RemoveAll(this);
}

void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputMapping();
	
	SetupHUD();
	SetupPlayerReference();
	CreateBindings();
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

void AFirstPersonPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!FirstPersonCharacter)
		SetupPlayerReference();
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

void AFirstPersonPlayerController::OnWeaponFire(int CurrentAmmo, int TotalAmmo)
{
	if(MainHUDWidget)
		MainHUDWidget->OnWeaponFire(CurrentAmmo);
}

void AFirstPersonPlayerController::OnWeaponReload(int CurrentAmmo, int TotalAmmo)
{
	if(MainHUDWidget)
		MainHUDWidget->OnWeaponReload(CurrentAmmo, TotalAmmo);
}

void AFirstPersonPlayerController::OnWeaponChange(int CurrentAmmo, int TotalAmmo)
{
	if(MainHUDWidget && FirstPersonCharacter)
		MainHUDWidget->OnWeaponChange(FirstPersonCharacter->GetCurrentWeaponData(), CurrentAmmo, TotalAmmo);
}

void AFirstPersonPlayerController::OnHealthChange(float CurrentHealth, float MaxHealth)
{
	if(MainHUDWidget)
		MainHUDWidget->OnHealthUpdated(CurrentHealth, MaxHealth);
}
