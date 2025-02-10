// Copyright Hola Games


#include "Misc/AuraGameSettings.h"

UAuraGameSettings::UAuraGameSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	typedef ETeamAttitude::Type EA;
	TeamAttitudes = {
		{ EA::Friendly, EA::Neutral,  EA::Neutral }, // Neutral
		{ EA::Neutral, EA::Friendly, EA::Hostile }, // Team1
		{ EA::Neutral, EA::Hostile,  EA::Friendly }, // Team2
	};
}

const UAuraGameSettings* UAuraGameSettings::Get()
{
	return GetDefault<UAuraGameSettings>();
}

ETeamAttitude::Type UAuraGameSettings::GetAttitude(FGenericTeamId Of, FGenericTeamId Towards)
{
	const TArray<FAuraTeamAttitude>& TeamAttitudes = UAuraGameSettings::Get()->TeamAttitudes;
	const bool OfValid = TeamAttitudes.IsValidIndex(Of.GetId());
	const bool TowardsValid = TeamAttitudes.IsValidIndex(Towards.GetId());

	if (OfValid && TowardsValid)
	{
		const TArray<TEnumAsByte<ETeamAttitude::Type>>& Attitudes = TeamAttitudes[Of.GetId()].Attitudes;
		if (Attitudes.IsValidIndex(Towards.GetId()))
		{
			return Attitudes[Towards.GetId()];
		}
	}
	return ETeamAttitude::Neutral;
}
