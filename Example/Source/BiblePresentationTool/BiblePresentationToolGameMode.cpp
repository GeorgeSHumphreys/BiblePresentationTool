// Copyright Epic Games, Inc. All Rights Reserved.

#include "BiblePresentationToolGameMode.h"
#include "BiblePresentationToolCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABiblePresentationToolGameMode::ABiblePresentationToolGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
