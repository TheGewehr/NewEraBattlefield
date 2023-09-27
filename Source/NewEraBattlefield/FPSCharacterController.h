// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/PlayerController.h"
#include "FPSCharacterController.generated.h"


class NEWERABATTLEFIELD_API AWeaponBase;

/**
 * 
 */
UCLASS()
class NEWERABATTLEFIELD_API AFPSCharacterController : public APlayerController
{
	GENERATED_BODY()
public:

	// Stored ammo data for the player
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TMap<EAmmoType, int32> AmmoMap;

	// The amount of ammunition boxes that the player has
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	int AmmoBoxCount;
};
