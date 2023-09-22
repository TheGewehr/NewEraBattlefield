// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "../Weapons/WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Components/FirstPersonHealthComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "NewEraBattlefield/Controllers/FirstPersonPlayerController.h"
#include "NewEraBattlefield/UI/FirstPersonHUD.h"

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
		if(!Weapon->GetMesh()->AttachToComponent(this->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint"))))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't attach weapon to the player"));
		Weapon->SetOwner(this);
	}
	if(AWeaponBase* Weapon = SecondaryWeaponComponent->GetWeapon())
	{
		if(!Weapon->GetMesh()->AttachToComponent(this->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint"))))
			UE_LOG(LogTemp, Warning, TEXT("Couldn't attach weapon to the player"));
		Weapon->SetOwner(this);
		Weapon->GetMesh()->SetVisibility(false, true);
	}
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupWeaponAttachments();


	SelectedWeaponComponent = PrimaryWeaponComponent;
	SecondaryWeaponComponent->CreateDefaultWeapon();
	PrimaryWeaponComponent->CreateDefaultWeapon();
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstPersonCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if(const AFirstPersonPlayerController* PlayerController = Cast<AFirstPersonPlayerController>(GetController()))
	{
		if(AFirstPersonHUD* HUD = Cast<AFirstPersonHUD>(PlayerController->GetHUD()))
		{
			

			
			
		
				
		}
	}
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

float AFirstPersonCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	HealthComponent->TakeDamage(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

