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
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void SetupStimulusSource();

#pragma region IGenericTeamAgentInterface
public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { /** Do Nothing */};
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
 
private:
	FGenericTeamId TeamId;
#pragma endregion

private:
	virtual int32 GetActorLevel() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionStimuliSourceComponent> StimulusSource;
};
