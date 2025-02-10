// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Game/AuraTeamAttitude.h"
#include "AuraGameSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig)
class AURA_API UAuraGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(Category = "Artificial Intelligence", EditAnywhere, BlueprintReadOnly, Config)
	TArray<FAuraTeamAttitude> TeamAttitudes;

public:

	UAuraGameSettings(const FObjectInitializer& ObjectInitializer);

	static const UAuraGameSettings* Get();

	UFUNCTION(Category = "Artificial Intelligence", BlueprintPure)
	static ETeamAttitude::Type GetAttitude(FGenericTeamId Of, FGenericTeamId Towards);
};
