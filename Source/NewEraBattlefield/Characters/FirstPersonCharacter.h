// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NewEraBattlefield/Weapons/WeaponComponent.h"
#include "../Weapons/WeaponBase.h"
#include "FirstPersonCharacter.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWeaponUpdate, int, int);

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
	void SetupBindings();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Player Actions
	void Move(const FVector2D& Movement);
	void Look(const FVector2D& Look);
	void Shoot();
	void Aim();
	void PickUp();
	virtual void Jump() override;
	void Reload();
	
	void SetupDefaultWeapons();
	
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	bool HasRifle() const { return SelectedWeaponComponent != nullptr ? SelectedWeaponComponent->HasWeapon() : false; }
	
	const FWeaponData& GetCurrentWeaponData() const { return SelectedWeaponComponent->GetWeapon()->GetWeaponData(); }
	
	// Components
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

	UPROPERTY(BlueprintReadOnly)
	UWeaponComponent* SelectedWeaponComponent = nullptr;

	// Delegates
	FOnWeaponUpdate OnWeaponChangedDelegate;
	FOnWeaponUpdate OnWeaponFireDelegate;
	FOnWeaponUpdate OnWeaponReloadDelegate;
};
