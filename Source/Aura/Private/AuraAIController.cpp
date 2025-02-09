// Copyright Hola Games


#include "AuraAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AAuraAIController::AAuraAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetGenericTeamId(FGenericTeamId(2));
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>("StateTreeAIComponent");
	SetupPerceptionSystem();
}

void AAuraAIController::SetupPerceptionSystem()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	if (SightConfig != nullptr
	 || HearingConfig != nullptr
	 || DamageConfig != nullptr)
	{
		SetPerceptionComponent(*PerceptionComponent);
	}

	if (SightConfig != nullptr)
	{
		SightConfig->SightRadius = 800.f;
		SightConfig->LoseSightRadius = 1200.f;
		SightConfig->PeripheralVisionAngleDegrees = 60.F;
		SightConfig->SetMaxAge(
			5.F); // seconds - perceived stimulus forgotten after this time
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		PerceptionComponent->ConfigureSense(*SightConfig);
		PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	}

	if (HearingConfig != nullptr)
	{
		HearingConfig->HearingRange = 10000.f;
		HearingConfig->SetMaxAge(5.f);
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		
		PerceptionComponent->ConfigureSense(*HearingConfig);
	}

	if (DamageConfig != nullptr)
	{
		DamageConfig->SetMaxAge(5.f);
		
		PerceptionComponent->ConfigureSense(*DamageConfig);
	}

	PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &ThisClass::OnPerceptionInfoUpdated);
}

void AAuraAIController::HandleSensedSight(const FActorPerceptionUpdateInfo& UpdateInfo)
{
}

void AAuraAIController::HandleSensedHearing(const FActorPerceptionUpdateInfo& UpdateInfo)
{
}

void AAuraAIController::HandleSensedDamage(const FActorPerceptionUpdateInfo& UpdateInfo)
{
}

void AAuraAIController::OnPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if (UpdateInfo.Stimulus.WasSuccessfullySensed())
	{
		if (UpdateInfo.Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			HandleSensedSight(UpdateInfo);
		}
		else if (UpdateInfo.Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			HandleSensedHearing(UpdateInfo);
		}
		else if (UpdateInfo.Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
		{
			HandleSensedDamage(UpdateInfo);
		}
	}
}
