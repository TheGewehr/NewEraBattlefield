// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FirstPersonHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);
DECLARE_MULTICAST_DELEGATE(FOnDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWERABATTLEFIELD_API UFirstPersonHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFirstPersonHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void TakeDamage(const float DamageAmount);
	void Heal(const float HealAmount);

	void Die();
	
	// Resets the component, sets the health to the max health and calls OnHealthChanged delegate
	void Reset();
	
	FOnHealthChanged OnHealthChanged;
	FOnDie OnDie;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxHealth() const { return MaxHealth; }
	
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.f;

};
