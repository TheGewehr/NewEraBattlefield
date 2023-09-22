// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonHUD.h"

#include "FirstPersonHUDWidget.h"
#include "NewEraBattlefield/Characters/FirstPersonCharacter.h"
#include "NewEraBattlefield/Components/FirstPersonHealthComponent.h"

void AFirstPersonHUD::BindCallbacks()
{
	// Setup callbacks
	Pawn = Cast<AFirstPersonCharacter>(GetOwningPawn());
	if(Pawn)
	{
		Pawn->HealthComponent->OnHealthChanged.AddDynamic(this, &AFirstPersonHUD::OnHealthChanged);
		Pawn->OnWeaponFire.BindDynamic(this, &AFirstPersonHUD::OnWeaponFired);
		Pawn->OnWeaponReload.BindDynamic(this, &AFirstPersonHUD::OnWeaponReload);
		Pawn->OnWeaponChanged.BindDynamic(this, &AFirstPersonHUD::OnWeaponChanged);

		if(Pawn->SelectedWeaponComponent)
			Pawn->SelectedWeaponComponent->SelectWeapon();
	}
}

void AFirstPersonHUD::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UFirstPersonHUDWidget>(GetGameInstance(), MainWidgetClass);
	MainWidget->AddToViewport(99);

	BindCallbacks();
}

void AFirstPersonHUD::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	MainWidget->OnHealthUpdated(CurrentHealth, MaxHealth);
	
}

void AFirstPersonHUD::OnWeaponFired(int CurrentAmmo, int TotalAmmo)
{
	MainWidget->OnWeaponFire(CurrentAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Weapon fired event!"));
}

void AFirstPersonHUD::OnWeaponReload(int CurrentAmmo, int TotalAmmo)
{
	MainWidget->OnWeaponReload(CurrentAmmo, TotalAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Weapon reload event!"));
}

void AFirstPersonHUD::OnWeaponChanged(int CurrentAmmo, int TotalAmmo)
{
	MainWidget->OnWeaponChange(Pawn->GetCurrentWeaponData(),CurrentAmmo, TotalAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Weapon changed event!"));
}



