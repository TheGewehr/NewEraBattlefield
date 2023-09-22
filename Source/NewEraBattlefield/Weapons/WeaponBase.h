// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "../Projectiles/ProjectileBase.h"
#include "WeaponBase.generated.h"

UENUM()
enum class EFireType
{
	FHitScan UMETA(DisplayName = "Hit Scan"),
	FProjectile UMETA(DisplayName = "Projectile")
};

UENUM()
enum class EWeaponType
{
	WAutomatic UMETA(DisplayName = "Automatic"),
	WSingle UMETA(DisplayName = "Single"),
	WBurst UMETA(DisplayName = "Burst")
};

// Stores all the data needed for AWeaponBase class
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFireType FireType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Recoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxTotalAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* MuzzleFlashEffect;
};


UCLASS()
class NEWERABATTLEFIELD_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	
	virtual void FireHitScan();
	virtual void FireProjectile();

public:
	// Attempts to fire the gun and returns the result
	UFUNCTION(BlueprintCallable)
	bool Fire();

	UFUNCTION(BlueprintCallable)
	bool Reload();
	
	UFUNCTION(BlueprintCallable)
	const FWeaponData& GetWeaponData() const { return WeaponData; } 
	uint32 GetCurrentAmmo() const { return CurrentAmmo; }
	uint32 GetTotalAmmoAmount() const { return TotalAmmoAmount; }

	
	USkeletalMeshComponent* GetMesh() const { return Mesh; }
private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootSceneComponent = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> Projectile;
	
	// Weapon data should be initialized when creating the blueprint
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category=Weapon, meta = (AllowPrivateAccess = "true"))
	FWeaponData WeaponData;

	UPROPERTY(VisibleAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool IsFiring = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int CurrentAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int TotalAmmoAmount; // Total reserve ammo for reloading mags

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnOffset = 0.0f;

	
	float TimeBetweenShoots = 0.f;
};
