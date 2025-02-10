// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/StateTreeAIComponent.h"
#include "Game/AuraTeamAttitude.h"
#include "AuraAIController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAuraAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = "Artificial Intelligence", BlueprintReadWrite, EditAnywhere)
	EAuraGameTeam AITeamID;

#pragma region IGenericTeamAgentInterface
public:
	void SetGenericTeamId(const EAuraGameTeam InTeamID);
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
#pragma endregion
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateTreeAIComponent> StateTreeAIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAISenseConfig_Hearing> HearingConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAISenseConfig_Damage> DamageConfig;

	void SetupPerceptionSystem();

	void HandleSensedSight(const FActorPerceptionUpdateInfo& UpdateInfo);
	void HandleSensedHearing(const FActorPerceptionUpdateInfo& UpdateInfo);
	void HandleSensedDamage(const FActorPerceptionUpdateInfo& UpdateInfo);
	
	UFUNCTION()
	void OnPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo);
};
