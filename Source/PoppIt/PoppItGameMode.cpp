// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PoppItGameMode.h"
#include "PoppItCharacter.h"
#include "UObject/ConstructorHelpers.h"

APoppItGameMode::APoppItGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GamePlay/Blueprints/Character_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
