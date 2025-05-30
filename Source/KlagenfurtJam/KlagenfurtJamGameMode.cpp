// Copyright Epic Games, Inc. All Rights Reserved.

#include "KlagenfurtJamGameMode.h"
#include "KlagenfurtJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKlagenfurtJamGameMode::AKlagenfurtJamGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
