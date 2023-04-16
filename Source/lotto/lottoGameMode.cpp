// Copyright Epic Games, Inc. All Rights Reserved.

#include "lottoGameMode.h"
#include "lottoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AlottoGameMode::AlottoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
