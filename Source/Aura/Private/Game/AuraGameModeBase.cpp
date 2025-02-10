// Copyright Hola Games


#include "Game/AuraGameModeBase.h"
#include "Misc/AuraGameSettings.h"

void AAuraGameModeBase::StartPlay()
{
	Super::StartPlay();

	FGenericTeamId::SetAttitudeSolver(&UAuraGameSettings::GetAttitude);
}
