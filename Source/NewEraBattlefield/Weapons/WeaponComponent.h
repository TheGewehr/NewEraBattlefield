// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AFirstPersonCharacter;
class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWERABATTLEFIELD_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();
	void CreateDefaultWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetOwner(AFirstPersonCharacter* Owner) { FirstPersonCharacter = Owner; }
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AttachWeapon(AFirstPersonCharacter* Owner, AWeaponBase* WeaponToAttach);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Reload();
	
	FORCEINLINE bool HasWeapon() const { return Weapon != nullptr; }
	FORCEINLINE AWeaponBase* GetWeapon() const { return Weapon; }

	UFUNCTION(BlueprintCallable)
	void SelectWeapon();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponBase> StartingWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = Player, meta = (AllowPrivateAccess = "true"))
	AFirstPersonCharacter* FirstPersonCharacter = nullptr;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* Weapon = nullptr;
};
