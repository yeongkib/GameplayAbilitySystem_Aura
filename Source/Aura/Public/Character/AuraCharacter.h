// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

#pragma region IGenericTeamAgentInterface
public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { /** Do Nothing */};
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
 
private:
	FGenericTeamId TeamId;
#pragma endregion
	
#pragma endregion
	virtual int32 GetActorLevel() override;
#pragma region Combat Interface

private:
	virtual void InitAbilityActorInfo() override;
};
