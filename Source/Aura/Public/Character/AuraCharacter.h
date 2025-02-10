// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Character/AuraCharacterBase.h"
#include "Game/AuraTeamAttitude.h"
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

// Pawn Class don’t need StimuliSourceComponent.
// RegisterForSense, RegisterWithPerceptionSystem functions are call GetWorld(),
// so have to call these function at PostInitializeComponents or BeginPlay.
// private:
// 	void SetupStimulusSource();

#pragma region IGenericTeamAgentInterface
public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { /** Do Nothing */};
	virtual FGenericTeamId GetGenericTeamId() const override;
 
private:
	EAuraGameTeam TeamId;
#pragma endregion

private:
	virtual int32 GetActorLevel() override;
	virtual void InitAbilityActorInfo() override;
};
