// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class NEWERABATTLEFIELD_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Damage;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float SpeedInMetersPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float WeightInKg;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;
	
	// Functions
	AProjectileBase();

	virtual void BeginPlay() override;

};

/*
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Bullet.generated.h"

UCLASS()
class YOURPROJECT_API ABullet : public AActor
{
	GENERATED_BODY()

public:	
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float SpeedInMetersPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float WeightInKg;

	// Functions
	ABullet();

	virtual void BeginPlay() override;
};
*/
