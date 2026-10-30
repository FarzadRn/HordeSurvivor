#include "Core/HSGameMode.h"
#include "Actors/Player/HSPlayerState.h"


AHSGameMode::AHSGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = AHSPlayerState::StaticClass();
}