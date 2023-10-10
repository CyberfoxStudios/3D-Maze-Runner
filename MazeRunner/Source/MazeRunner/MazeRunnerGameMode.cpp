// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazeRunnerGameMode.h"
#include "MazeRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMazeRunnerGameMode::AMazeRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
