// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogFPSController, Log, All);

class UInputMappingContext;
class UInputAction;
class UFirstPersonHUDWidget;
/*
 * Base class that controls the input and actions for the FirstPersonCharacter
 */
UCLASS()
class NEWERABATTLEFIELD_API AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFirstPersonPlayerController();
	virtual ~AFirstPersonPlayerController() override;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	void SetupInputMapping() const;
	void SetupPlayerReference();
	
	void SetupHUD();

	// Binding handling
	void CreateBindings();
	void RemoveBindings();

	// Input handling callbacks
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleAim(const FInputActionValue& Value);
	void HandleShoot(const FInputActionValue& Value);
	void HandlePickUpItem(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandleReload(const FInputActionValue& Value);
public:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext = nullptr;

	// Input actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Move_InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Look_InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Aim_InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Shoot_InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PickItem_InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Jump_InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Reload_InputAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class AFirstPersonCharacter* FirstPersonCharacter = nullptr;

	UFUNCTION()
	void OnWeaponFire(int CurrentAmmo, int TotalAmmo);

	UFUNCTION()
	void OnWeaponReload(int CurrentAmmo, int TotalAmmo);
	
	UFUNCTION()
	void OnWeaponChange(int CurrentAmmo, int TotalAmmo);

	UFUNCTION()
	void OnHealthChange(float CurrentHealth, float MaxHealth);
	
	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> MainHUDClass;

	UPROPERTY(VisibleDefaultsOnly)
	UFirstPersonHUDWidget* MainHUDWidget = nullptr;
};
