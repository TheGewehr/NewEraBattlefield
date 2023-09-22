// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	RootComponent = RootSceneComponent;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeBetweenShoots += DeltaTime;
}

void AWeaponBase::Fire()
{
	// Control weapon timing
	if(TimeBetweenShoots < 1.f / WeaponData.FireRate)
		return;
	// Reset the timing
	TimeBetweenShoots = 0.f;

	UE_LOG(LogTemp, Warning, TEXT("Shotting!"));

	
	DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), 90, 2, FColor::Red);
	
	switch (WeaponData.FireType)
	{
	case EFireType::FHitScan: FireHitScan(); break;
	case EFireType::FProjectile: FireProjectile(); break;
	}

	
	if(WeaponData.MuzzleFlashEffect)
		UGameplayStatics::SpawnEmitterAttached(WeaponData.MuzzleFlashEffect, Mesh, TEXT("Muzzle"));
}

void AWeaponBase::FireHitScan()
{
}

void AWeaponBase::FireProjectile()
{
	if(Projectile)
	{
		
	}
}

