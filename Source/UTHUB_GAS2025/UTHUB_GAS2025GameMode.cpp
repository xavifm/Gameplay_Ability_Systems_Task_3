// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS2025GameMode.h"
#include "UTHUB_GAS2025PlayerController.h"
#include "UTHUB_GAS2025Character.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_GAS2025GameMode::AUTHUB_GAS2025GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUTHUB_GAS2025PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}