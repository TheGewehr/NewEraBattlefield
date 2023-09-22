// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponBase.h"
#include "NewEraBattlefield/Characters/FirstPersonCharacter.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UWeaponComponent::CreateDefaultWeapon()
{
	Weapon = GetWorld()->SpawnActor<AWeaponBase>(StartingWeapon);
	AttachWeapon(FirstPersonCharacter, Weapon);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::AttachWeapon(AFirstPersonCharacter* Owner, AWeaponBase* WeaponToAttach)
{
	Weapon = WeaponToAttach;
	FirstPersonCharacter = Owner;
}

void UWeaponComponent::Fire()
{
	if(!Weapon)
		return;
	if(Weapon->Fire())
	{
		if(!FirstPersonCharacter->OnWeaponFire.ExecuteIfBound(Weapon->GetCurrentAmmo(), Weapon->GetTotalAmmoAmount()))
			UE_LOG(LogTemp, Warning, TEXT("Called OnWeaponFire but not function was bound!"));
	}
}

void UWeaponComponent::Reload()
{
	if(!Weapon)
		return;

	if(Weapon->Reload())
	{
		if(!FirstPersonCharacter->OnWeaponReload.ExecuteIfBound(Weapon->GetCurrentAmmo(), Weapon->GetTotalAmmoAmount()))
			UE_LOG(LogTemp, Warning, TEXT("Called OnWeaponReload but not function was bound!"));
	}
}

void UWeaponComponent::SelectWeapon()
{
	if(!FirstPersonCharacter || !Weapon)
		return;
	
	if(!FirstPersonCharacter->OnWeaponChanged.ExecuteIfBound(Weapon->GetCurrentAmmo(), Weapon->GetTotalAmmoAmount()))
		UE_LOG(LogTemp, Warning, TEXT("Called OnWeaponChanged but not function was bound!"));
}

