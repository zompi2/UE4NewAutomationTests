// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AutoTestGameMode.h"
#include "AutoTestHUD.h"
#include "AutoTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAutoTestGameMode::AAutoTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAutoTestHUD::StaticClass();
}
