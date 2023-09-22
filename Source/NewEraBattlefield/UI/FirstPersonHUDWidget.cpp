// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonHUDWidget.h"

void UFirstPersonHUDWidget::UpdateHealth(float NewCurrentHealth, float NewMaxHealth)
{
	CurrentHealth = NewCurrentHealth;
	MaxHealth = NewMaxHealth;
	OnHealthUpdated();
}

void UFirstPersonHUDWidget::OnHealthUpdated_Implementation()
{
}
