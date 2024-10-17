// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmartAIGameMode.h"
#include "SmartAICharacter.h"
#include "UObject/ConstructorHelpers.h"

ASmartAIGameMode::ASmartAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
