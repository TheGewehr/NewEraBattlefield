// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "../Weapons_F/WeaponComponent.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Setup components
	PrimaryWeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Primary Weapon"));
	SecondaryWeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Secondary Weapon"));

	PrimaryWeaponComponent->SetOwner(this);
	SecondaryWeaponComponent->SetOwner(this);

	SecondaryWeaponComponent->Deactivate();


}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	SelectedWeaponComponent = PrimaryWeaponComponent;
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstPersonCharacter::Move(const FVector2D& Movement)
{
	if(!Controller)
		return;

	AddMovementInput(GetActorForwardVector(), Movement.Y);
	AddMovementInput(GetActorRightVector(), Movement.X);
}

void AFirstPersonCharacter::Look(const FVector2D& Look)
{
	if (!Controller)
		return;
	
	AddControllerYawInput(Look.X);
	AddControllerPitchInput(-Look.Y);
}

void AFirstPersonCharacter::Shoot()
{
	if(!SelectedWeaponComponent)
		return;

	SelectedWeaponComponent->Fire();
}

void AFirstPersonCharacter::Aim()
{
}

void AFirstPersonCharacter::PickUp()
{
}

void AFirstPersonCharacter::Jump()
{
	Super::Jump();
	
}

void AFirstPersonCharacter::Reload()
{
}

