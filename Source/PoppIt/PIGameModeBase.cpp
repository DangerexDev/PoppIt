// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PIGameModeBase.h"
#include "PIPlayerCharacterBase.h"
#include "UObject/ConstructorHelpers.h"

APIGameModeBase::APIGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Gameplay/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
