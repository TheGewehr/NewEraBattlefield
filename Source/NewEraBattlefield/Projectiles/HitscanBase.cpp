// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanBase.h"

// Sets default values
AHitscanBase::AHitscanBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsHitScanActive = false;

}

// Called when the game starts or when spawned
void AHitscanBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHitscanBase::StartHitscan(FVector StartPoint, FVector ForwardVector)
{
	// Initialize the hitscan parameters
	CurrentHitscanPosition = StartPoint;
	CurrentForwardVector = ForwardVector;
	SimulationHitscanData = InitialHitscanData;

	// Start the hitscan
	bIsHitScanActive = true;
}

bool AHitscanBase::SimulateHitscanStep()
{
	SimulationHitscanData.CurrentHitScanTime += CurrentDeltaTime;
    
	FVector BulletVelocity = CurrentForwardVector * (SimulationHitscanData.SpeedMetersPerSecond * 100.0f);
	BulletVelocity += (Gravity + Drag + Wind) * CurrentDeltaTime;

	FVector EndPoint = ((BulletVelocity * CurrentDeltaTime) + CurrentHitscanPosition);
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CurrentHitscanPosition, EndPoint, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		// Handle hit logic
		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitResult.GetComponent()->IsSimulatingPhysics())
		{
			FVector ImpactForce = BulletVelocity * SimulationHitscanData.WeightInKg;
			HitResult.GetComponent()->AddForceAtLocation(ImpactForce, HitResult.ImpactPoint, HitResult.BoneName);
		}

		// Calculate and apply damage
		// UGameplayStatics::ApplyPointDamage(HitActor, HitscanData.Damage, CurrentForwardVector, HitResult, nullptr, HitActor, HitscanData.DamageType);
	}

	CurrentHitscanPosition = EndPoint;

	return bHit;
}

// Called every frame
void AHitscanBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDeltaTime = DeltaTime;

	if (bIsHitScanActive)
	{
		// Update only if hitscan is active
		bool bHit = SimulateHitscanStep();

		if (bHit || SimulationHitscanData.CurrentHitScanTime >= InitialHitscanData.MaxFlightTime)
		{
			// Stop hitscan if we hit something or if we've reached max flight time
			bIsHitScanActive = false;
		}
	}
}

