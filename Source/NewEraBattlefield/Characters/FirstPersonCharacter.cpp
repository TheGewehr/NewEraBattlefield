// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "../Weapons/WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Components/FirstPersonHealthComponent.h"
#include "NewEraBattlefield/Controllers/FirstPersonPlayerController.h"
#include "NewEraBattlefield/UI/FirstPersonHUDWidget.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Setup components
	PrimaryWeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Primary Weapon"));
	SecondaryWeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Secondary Weapon"));
	PrimaryWeaponComponent->SetOwner(this);
	//SecondaryWeaponComponent->SetOwner(this);
	SecondaryWeaponComponent->Deactivate();

	// Set the mesh to not bee seen by the owner
	GetMesh()->SetOwnerNoSee(true);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	// Create the health component
	HealthComponent = CreateDefaultSubobject<UFirstPersonHealthComponent>(TEXT("Health Component"));
}

void AFirstPersonCharacter::SetupWeaponAttachments()
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	if(AWeaponBase* Weapon = PrimaryWeaponComponent->GetWeapon())
	{
		Weapon->SetOwner(this);

		if(!Weapon->GetMesh()->AttachToComponent(this->GetMesh(), AttachmentRules, FName(TEXT("GripPoint"))))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't attach weapon to the player"));
		
		if(!Weapon->GetMesh1P()->AttachToComponent(this->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint"))))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't attach weapon to the player"));
	}
	if(AWeaponBase* Weapon = SecondaryWeaponComponent->GetWeapon())
	{
		Weapon->SetOwner(this);

		if(!Weapon->GetMesh()->AttachToComponent(this->GetMesh(), AttachmentRules, FName(TEXT("GripPoint"))))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't attach weapon to the player"));
		
		if(!Weapon->GetMesh1P()->AttachToComponent(this->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint"))))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't attach weapon to the player"));
		
		Weapon->GetMesh()->SetVisibility(false, true);
		Weapon->GetMesh1P()->SetVisibility(false, true);
	}
}

void AFirstPersonCharacter::SetupBindings()
{
	HealthComponent->Reset();
}
void AFirstPersonCharacter::SetupDefaultWeapons()
{
	SecondaryWeaponComponent->CreateDefaultWeapon();
	PrimaryWeaponComponent->CreateDefaultWeapon();
	SelectedWeaponComponent = PrimaryWeaponComponent;

}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetupBindings();
	SetupDefaultWeapons();
	SetupWeaponAttachments();

	if(const AFirstPersonPlayerController* FPSController = Cast<AFirstPersonPlayerController>(GetController()))
	{
		if(FPSController->MainHUDWidget)
			FPSController->MainHUDWidget->OnReady();
	}
}

void AFirstPersonCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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

	// TODO: Change this in the future
	if(SelectedWeaponComponent->Fire())
	{
		UE_LOG(LogTemp, Warning, TEXT("Broadcasting Weapon fire!"));
		OnWeaponFireDelegate.Broadcast(SelectedWeaponComponent->GetWeapon()->GetCurrentAmmo(), SelectedWeaponComponent->GetWeapon()->GetTotalAmmoAmount());
	}
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
	if(!SelectedWeaponComponent)
		return;

	// TODO: Change this in the future
	if(SelectedWeaponComponent->Reload())
	{
		OnWeaponReloadDelegate.Broadcast(SelectedWeaponComponent->GetWeapon()->GetCurrentAmmo(), SelectedWeaponComponent->GetWeapon()->GetTotalAmmoAmount());
	}		
}


float AFirstPersonCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                        AController* EventInstigator, AActor* DamageCauser)
{
	HealthComponent->TakeDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

