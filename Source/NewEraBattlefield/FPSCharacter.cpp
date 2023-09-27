// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Components/InventoryComponent.h"

void AFPSCharacter::SetMovementState(EMovementState NewMovementState)
{
}

AFPSCharacter::AFPSCharacter()
{
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
}

void AFPSCharacter::ToggleCrouch()
{
}

void AFPSCharacter::StopCrouch(bool bToSprint)
{
}

void AFPSCharacter::ReleaseCrouch()
{
}

void AFPSCharacter::StartSprint()
{
}

void AFPSCharacter::StopSprint()
{
}

void AFPSCharacter::StartSlide()
{
}

void AFPSCharacter::StopSlide()
{
}

void AFPSCharacter::CheckVault()
{
}

void AFPSCharacter::Vault(FTransform TargetTransform)
{
}

void AFPSCharacter::CheckGroundAngle(float DeltaTime)
{
}

float AFPSCharacter::CheckRelativeMovementAngle(float DeltaTime) const
{
	const FVector MovementVector = GetVelocity();
	const FRotator MovementRotator = GetActorRotation();
	const FVector RelativeMovementVector = MovementRotator.UnrotateVector(MovementVector);

	if (bDrawDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Orange, FString::SanitizeFloat(FMath::Abs(RelativeMovementVector.HeadingAngle() * (180/PI))));    
	}
    
	return FMath::Abs(RelativeMovementVector.HeadingAngle());
}

bool AFPSCharacter::HasSpaceToStandUp()
{
	FVector CenterVector = GetActorLocation();
	CenterVector.Z += 44;

	const float CollisionCapsuleHeight = DefaultCapsuleHalfHeight - 17.0f;

	// Check to see if a capsule collision collides with the environment, if yes, we don't have space to stand up
	const FCollisionShape CollisionCapsule = FCollisionShape::MakeCapsule(30.0f, CollisionCapsuleHeight);

	if (bDrawDebug)
	{
		DrawDebugCapsule(GetWorld(), CenterVector, CollisionCapsuleHeight, 30.0f, FQuat::Identity, FColor::Red, false, 5.0f, 0, 3);
	}

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
    
	if (GetWorld()->SweepSingleByChannel(StandUpHit, CenterVector, CenterVector, FQuat::Identity, ECC_WorldStatic, CollisionCapsule, QueryParams))
	{
		/* confetti or smth idk */
		if (bDrawDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Stand up trace returned hit", true);
		}
		return false;
	}

	return true;
}

void AFPSCharacter::TimelineProgress(float Value)
{
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
}

void AFPSCharacter::StartAds()
{
}

void AFPSCharacter::StopAds()
{
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
