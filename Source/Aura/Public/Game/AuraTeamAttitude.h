// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "AuraTeamAttitude.generated.h"

UENUM(BlueprintType)
enum class EAuraGameTeam : uint8
{
	Neutral, // Everyone ignores this team
	Player,
	Enemy,
};

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAuraTeamAttitude
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TEnumAsByte<ETeamAttitude::Type>> Attitudes;

	FAuraTeamAttitude() {};

	FAuraTeamAttitude(std::initializer_list<TEnumAsByte<ETeamAttitude::Type>> InAttitudes):
		Attitudes(std::move(InAttitudes))
	{ };
};
