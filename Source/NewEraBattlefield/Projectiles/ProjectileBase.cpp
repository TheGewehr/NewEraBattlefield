// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Initialize Capsule Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));	
	RootComponent = CapsuleComponent;
	
	//FRotator CurrentRotation = CapsuleComponent->GetComponentRotation();
	//FRotator NewRotation = CurrentRotation.Add(0.f, 90.f, 0.f);
	//CapsuleComponent->SetWorldRotation(NewRotation);
	//CapsuleComponent->

	//FRotator CurrentRotation2 = RootComponent->GetComponentRotation();
	//FRotator NewRotation2 = CurrentRotation2.Add(0.f, 90.f, 0.f);
	//RootComponent->SetWorldRotation(NewRotation2);

	// Initialize Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	// Initialize properties
	Damage = 100.0f;
	SpeedInMetersPerSecond = 900.0f; // 900 m/s
	WeightInKg = 0.01f; // 10 grams in kg

	// Convert speed to cm/s for Unreal Engine
	ProjectileMovement->InitialSpeed = SpeedInMetersPerSecond * 100; 
	ProjectileMovement->MaxSpeed = SpeedInMetersPerSecond * 100;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	// You can put additional logic here, e.g., bind capsule overlap event to a function to apply damage
}

/*
#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
	// Initialize Capsule Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	// Initialize Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	// Initialize properties
	Damage = 50.0f;
	SpeedInMetersPerSecond = 900.0f; // 900 m/s
	WeightInKg = 0.01f; // 10 grams in kg

	// Convert speed to cm/s for Unreal Engine
	ProjectileMovement->InitialSpeed = SpeedInMetersPerSecond * 100; 
	ProjectileMovement->MaxSpeed = SpeedInMetersPerSecond * 100;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	// You can put additional logic here, e.g., bind capsule overlap event to a function to apply damage
}
*/