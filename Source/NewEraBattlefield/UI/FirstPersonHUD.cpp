// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonHUD.h"

#include "FirstPersonHUDWidget.h"
#include "NewEraBattlefield/Characters/FirstPersonCharacter.h"
#include "NewEraBattlefield/Components/FirstPersonHealthComponent.h"

void AFirstPersonHUD::BeginPlay()
{
	Super::BeginPlay();
	MainWidget = CreateWidget<UFirstPersonHUDWidget>(GetGameInstance(), MainWidgetClass);
	MainWidget->AddToViewport(99);
	if(const AFirstPersonCharacter* Pawn = Cast<AFirstPersonCharacter>(GetOwningPawn()))
	{
		Pawn->HealthComponent->OnHealthChanged.AddDynamic(this, &AFirstPersonHUD::OnHealthChanged);
	}
}

void AFirstPersonHUD::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	MainWidget->UpdateHealth(CurrentHealth, MaxHealth);
}


