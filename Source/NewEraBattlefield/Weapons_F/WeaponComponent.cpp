// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponBase.h"
#include "NewEraBattlefield/Characters_F/FirstPersonCharacter.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapon = GetWorld()->SpawnActor<AWeaponBase>(StartingWeapon);
	AttachWeapon(FirstPersonCharacter, Weapon);
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

	if(Weapon && FirstPersonCharacter)
	{
		const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(FirstPersonCharacter->GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));
		Weapon->SetOwner(FirstPersonCharacter);
	}
}

void UWeaponComponent::Fire()
{
	if(!Weapon)
		return;
	Weapon->Fire();
}

