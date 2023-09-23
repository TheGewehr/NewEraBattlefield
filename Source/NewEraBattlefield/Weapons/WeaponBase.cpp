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
	Mesh->SetOwnerNoSee(true);
	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh 1P"));
	Mesh1P->SetupAttachment(RootSceneComponent);
	Mesh1P->SetOnlyOwnerSee(true);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = WeaponData.MaxClipSize;
	TotalAmmoAmount = WeaponData.MaxTotalAmmo;
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeBetweenShoots += DeltaTime;

}

bool AWeaponBase::Fire()
{
	// Check if the weapon has enough ammo
	if(CurrentAmmo <= 0)
		return false;
	
	// Control weapon timing
	if(TimeBetweenShoots < 1.f / WeaponData.FireRate)
		return false;
	
	// Reset the timing and subtract the ammo 
	TimeBetweenShoots = 0.f;
	CurrentAmmo--;
	DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), 90, 2, FColor::Red);
	
	switch (WeaponData.FireType)
	{
	case EFireType::FHitScan: FireHitScan(); break;
	case EFireType::FProjectile: FireProjectile(); break;
	}
	
	if(WeaponData.MuzzleFlashEffect)
		UGameplayStatics::SpawnEmitterAttached(WeaponData.MuzzleFlashEffect, Mesh, TEXT("Muzzle"));

	return true;
}

bool AWeaponBase::Reload()
{
	if(TotalAmmoAmount > 0)
	{
		TotalAmmoAmount -= WeaponData.MaxClipSize - CurrentAmmo;

		if(TotalAmmoAmount >= WeaponData.MaxClipSize)	
			CurrentAmmo = WeaponData.MaxClipSize;
		else
			CurrentAmmo = TotalAmmoAmount;
		
		return true;
	}
	
	return false;
}

bool AWeaponBase::RequestReload()
{
	return true;
}


void AWeaponBase::FireHitScan()
{

	AHitscanBase* HitscanInstance = GetWorld()->SpawnActor<AHitscanBase>(Hitscan);

	// Now that you have an instance, you can access its members.
	if (HitscanInstance)
	{
		HitscanInstance->StartHitscan(GetActorLocation() + GetActorForwardVector() * SpawnOffset,GetActorForwardVector());
	}
}


void AWeaponBase::FireProjectile()
{
	if(Projectile)
	{
		// Get the spawn location and rotation in front of the weapon
		const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * SpawnOffset;
		const FRotator SpawnRotation = GetActorRotation().Add(0.f, 90.f, 0.f) ;

		// Spawn the projectile at the calculated location and rotation
		//TSubclassOf<AProjectileBase>* SpawnedProjectile = GetWorld()->SpawnActor<TSubclassOf<AProjectileBase>>(Projectile, SpawnLocation, SpawnRotation, FActorSpawnParameters());
		//AMyBlueprintActor* SpawnedActor = GetWorld()->SpawnActor<AMyBlueprintActor>(AMyBlueprintActor::StaticClass(), SpawnLocation, SpawnRotation);
		
		AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(Projectile,SpawnLocation, SpawnRotation, FActorSpawnParameters());

		UE_LOG(LogTemp, Warning, TEXT("Projectile Fired!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile variable is null!"));
	}
}

