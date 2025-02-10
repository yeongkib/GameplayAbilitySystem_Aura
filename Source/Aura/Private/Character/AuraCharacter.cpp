// Copyright Hola Games


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IGenericTeamAgentInterface* ControllerAsTeamProvider = Cast<IGenericTeamAgentInterface>(NewController))
	{
		TeamId = static_cast<EAuraGameTeam>(ControllerAsTeamProvider->GetGenericTeamId().GetId());
	}
	// Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Fixes issue where skills (such as fire bolt) is not firing on the server as notify event is not being received.
	// Enabling auto-flush ensures that network packets are immediately sent to the recipient without additional delay
	if (UNetConnection* Connection = GetNetConnection())
	{
		Connection->SetAutoFlush(true);
	}
	
	// Init ability actor info for the client
	InitAbilityActorInfo();
}

FGenericTeamId AAuraCharacter::GetGenericTeamId() const
{
	return static_cast<uint8>(TeamId);
}

// void AAuraCharacter::SetupStimulusSource()
// {
// 	check(StimulusSource);
// 	
// 	StimulusSource->RegisterForSense(UAISense_Sight::StaticClass());
// 	StimulusSource->RegisterForSense(UAISense_Hearing::StaticClass());
// 	StimulusSource->RegisterWithPerceptionSystem();
// }

int32 AAuraCharacter::GetActorLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetActorLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	if (AAuraPlayerController* AuraPlayerController = GetController<AAuraPlayerController>())
	{
		if (AAuraHUD* AuraHUD = AuraPlayerController->GetHUD<AAuraHUD>())
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}
