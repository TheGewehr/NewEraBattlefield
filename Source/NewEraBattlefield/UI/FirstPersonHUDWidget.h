// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirstPersonHUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class NEWERABATTLEFIELD_API UFirstPersonHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintNativeEvent)
	void OnHealthUpdated();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentHealth;
};
