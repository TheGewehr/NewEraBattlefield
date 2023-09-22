// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonHUD.h"

#include "FirstPersonHUDWidget.h"
#include "NewEraBattlefield/Characters/FirstPersonCharacter.h"
#include "NewEraBattlefield/Components/FirstPersonHealthComponent.h"

void AFirstPersonHUD::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UFirstPersonHUDWidget>(GetGameInstance(), MainWidgetClass);
	MainWidget->AddToViewport(99);

	// Setup callbacks
	Pawn = Cast<AFirstPersonCharacter>(GetOwningPawn());
	if(Pawn)
	{
		Pawn->HealthComponent->OnHealthChanged.AddDynamic(this, &AFirstPersonHUD::OnHealthChanged);
		Pawn->OnWeaponFire.AddDynamic(this, &AFirstPersonHUD::OnWeaponFired);
		Pawn->OnWeaponReload.AddDynamic(this, &AFirstPersonHUD::OnWeaponReload);
		Pawn->OnWeaponChanged.AddDynamic(this, &AFirstPersonHUD::OnWeaponChanged);
	}
}

void AFirstPersonHUD::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	MainWidget->OnHealthUpdated(CurrentHealth, MaxHealth);
}

void AFirstPersonHUD::OnWeaponFired(int CurrentAmmo, int TotalAmmo)
{
	MainWidget->OnWeaponFire(CurrentAmmo);
}

void AFirstPersonHUD::OnWeaponReload(int CurrentAmmo, int TotalAmmo)
{
	MainWidget->OnWeaponReload(CurrentAmmo, TotalAmmo);
}

void AFirstPersonHUD::OnWeaponChanged(int CurrentAmmo, int TotalAmmo)
{
	MainWidget->OnWeaponChange(Pawn->GetCurrentWeaponData(),CurrentAmmo, TotalAmmo);
}



