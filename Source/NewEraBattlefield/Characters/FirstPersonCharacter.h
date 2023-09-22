// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NewEraBattlefield/Weapons/WeaponComponent.h"
#include "../Weapons/WeaponBase.h"
#include "FirstPersonCharacter.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnWeaponUpdate, int, CurrentAmmo, int, TotalAmmo);

class UWeaponComponent;
class UCameraComponent;

UCLASS()
class NEWERABATTLEFIELD_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();
	void SetupWeaponAttachments();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyControllerChanged() override;	
	// Player Actions
	void Move(const FVector2D& Movement);
	void Look(const FVector2D& Look);
	void Shoot();
	void Aim();
	void PickUp();
	virtual void Jump() override;
	void Reload();
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	bool HasRifle() const { return SelectedWeaponComponent != nullptr ? SelectedWeaponComponent->HasWeapon() : false; }

	UFUNCTION(BlueprintCallable)
	const FWeaponData& GetCurrentWeaponData() const { return SelectedWeaponComponent->GetWeapon()->GetWeaponData(); }
	
	UPROPERTY(VisibleDefaultsOnly,Category=Mesh)
	USkeletalMeshComponent* Mesh1P  = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category=Camera)
	UCameraComponent* FirstPersonCameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Health)
	class UFirstPersonHealthComponent* HealthComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Weapon)
	UWeaponComponent* PrimaryWeaponComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Weapon)
	UWeaponComponent* SecondaryWeaponComponent = nullptr;

	UPROPERTY()
	UWeaponComponent* SelectedWeaponComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FOnWeaponUpdate OnWeaponChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FOnWeaponUpdate OnWeaponFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FOnWeaponUpdate OnWeaponReload;
};
