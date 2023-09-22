// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewEraBattlefield/Weapons/WeaponBase.h"
#include "FirstPersonHUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class NEWERABATTLEFIELD_API UFirstPersonHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnHealthUpdated(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintNativeEvent)
	void OnWeaponFire(int CurrentAmmo);

	UFUNCTION(BlueprintNativeEvent)
	void OnWeaponReload(int CurrentAmount, int TotalAmmoAmount);

	UFUNCTION(BlueprintNativeEvent)
	void OnWeaponChange(const FWeaponData& WeaponData ,int CurrentAmount, int TotalAmount);
};
