// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


/** Enumerator holding the 4 types of ammunition that weapons can use (used as part of the FSingleWeaponParams struct)
 * and to keep track of the total ammo the player has (ammoMap) */
UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	Pistol       UMETA(DisplayName = "Pistol Ammo"),
	Rifle        UMETA(DisplayName = "Rifle Ammo"),
	Shotgun      UMETA(DisplayName = "Shotgun Ammo"),
	Special		 UMETA(DisplayName = "Special Ammo"),
};

/** Enumerator holding all the possible typed of attachment */
UENUM()
enum class EAttachmentType : uint8
{
	Barrel		UMETA(DisplayName = "Barrel Attachment"),
	Magazine	UMETA(DisplayName = "Magazine Attachment"),
	Sights		UMETA(DisplayName = "Sights Attachment"),
	Stock		UMETA(DispayName = "Stock Attachment"),
	Grip		UMETA(DispayName = "Grip Attachment"),
};

/** A struct containing all the animations needed by FPS Core, in order to simplify blueprint operations */
USTRUCT(BlueprintType)
struct FHandsAnimSet
{
	GENERATED_BODY()

	/** The walking BlendSpace */
	UPROPERTY(BlueprintReadOnly, Category = "Unique Weapon (No Attachments)")
	UBlendSpace* BS_Walk;

	/** The ADS Walking BlendSpace */
	UPROPERTY(BlueprintReadOnly, Category = "Unique Weapon (No Attachments)")
	UBlendSpace* BS_Ads_Walk;

	/** The Idle animation sequence */
	UPROPERTY(BlueprintReadOnly, Category = "Unique Weapon (No Attachments)")
	UAnimSequence* Anim_Idle;

	/** The ADS Idle animation sequence */
	UPROPERTY(BlueprintReadOnly, Category = "Unique Weapon (No Attachments)")
	UAnimSequence* Anim_Ads_Idle;
	
	/** Hand animation for when the player has no weapon, is idle, and is aiming down sights */
	UPROPERTY(BlueprintReadOnly, Category = "Animations | Sequences")
	UAnimSequence* Anim_Jump_Start;

	/** Hand animation for when the player has no weapon, is idle, and is aiming down sights */
	UPROPERTY(BlueprintReadOnly, Category = "Animations | Sequences")
	UAnimSequence* Anim_Jump_End;

	/** Hand animation for when the player has no weapon, is idle, and is aiming down sights */
	UPROPERTY(BlueprintReadOnly, Category = "Animations | Sequences")
	UAnimSequence* Anim_Fall;

	/** The sprinting animation sequence */
	UPROPERTY(BlueprintReadOnly, Category = "Unique Weapon (No Attachments)")
	UAnimSequence* Anim_Sprint;
};

UCLASS()
class NEWERABATTLEFIELD_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
