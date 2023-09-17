// Copyright Epic Games, Inc. All Rights Reserved.

#include "NewEraBattlefieldGameMode.h"
#include "NewEraBattlefieldCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANewEraBattlefieldGameMode::ANewEraBattlefieldGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
