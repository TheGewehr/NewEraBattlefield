// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FirstPersonHUD.generated.h"

class UFirstPersonHUDWidget;
/**
 * 
 */
UCLASS()
class NEWERABATTLEFIELD_API AFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(float CurrentHealth, float MaxHealth);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(VisibleDefaultsOnly)
	UFirstPersonHUDWidget* MainWidget = nullptr;
};
