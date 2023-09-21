// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

class UWeaponComponent;

UCLASS()
class NEWERABATTLEFIELD_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Weapon)
	UWeaponComponent* PrimaryWeaponComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Weapon)
	UWeaponComponent* SecondaryWeaponComponent = nullptr;

	UWeaponComponent* SelectedWeaponComponent = nullptr;
};
