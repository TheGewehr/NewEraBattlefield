// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NewEraBattlefieldGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEWERABATTLEFIELD_API UNewEraBattlefieldGameInstance : public UGameInstance
{
	GENERATED_BODY()
	virtual void OnStart() override;
	virtual void Init() override;
};
