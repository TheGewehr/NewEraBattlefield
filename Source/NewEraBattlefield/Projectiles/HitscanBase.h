// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitscanBase.generated.h"

//USTRUCT(BlueprintType)
//struct FWeaponData
//{
//	GENERATED_BODY()
//    
//	// Add the weapon-specific fields here, like in your original WeaponData struct
//};

USTRUCT(BlueprintType)
struct FHitscanData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitscanData")
	float SpeedMetersPerSecond = 900.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitscanData")
	float WeightInKg = 0.01f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitscanData")
	float Damage = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitscanData")
	float MaxFlightTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	float CurrentHitScanTime = 0.0f;

};

UCLASS()
class NEWERABATTLEFIELD_API AHitscanBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitscanBase();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool SimulateHitscanStep();

	FVector CurrentForwardVector;
	FVector CurrentHitscanPosition;

	FVector Gravity = FVector(0, 0, -9.81);
	FVector Wind = FVector(0, 0, 0); 
	FVector Drag = FVector(0, 0, 0);

	bool bIsHitScanActive = false;

	float CurrentDeltaTime = 0.0f;

	FHitscanData SimulationHitscanData;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartHitscan(FVector StartPoint, FVector ForwardVector);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitscanData")
	FHitscanData InitialHitscanData;	

};
