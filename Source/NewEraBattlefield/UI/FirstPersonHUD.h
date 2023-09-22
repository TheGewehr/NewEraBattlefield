// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FirstPersonHUD.generated.h"


struct FWeaponData;
class UFirstPersonHUDWidget;
/**
 * 
 */
UCLASS()
class NEWERABATTLEFIELD_API AFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void OnWeaponFired( int CurrentAmmo, int TotalAmmo);

	UFUNCTION(BlueprintCallable)
	void OnWeaponReload( int CurrentAmmo, int TotalAmmo);

	UFUNCTION(BlueprintCallable)
	void OnWeaponChanged(int CurrentAmmo, int TotalAmmo);

	UPROPERTY()
	class AFirstPersonCharacter* Pawn = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(VisibleDefaultsOnly)
	UFirstPersonHUDWidget* MainWidget = nullptr;
};
