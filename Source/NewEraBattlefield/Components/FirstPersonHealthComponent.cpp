// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonHealthComponent.h"

// Sets default values for this component's properties
UFirstPersonHealthComponent::UFirstPersonHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFirstPersonHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = MaxHealth;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}


// Called every frame
void UFirstPersonHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFirstPersonHealthComponent::TakeDamage(const float DamageAmount)
{
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UFirstPersonHealthComponent::Heal(const float HealAmount)
{
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UFirstPersonHealthComponent::Die()
{
	// TODO: Die actions
	OnDie.Broadcast();
}

