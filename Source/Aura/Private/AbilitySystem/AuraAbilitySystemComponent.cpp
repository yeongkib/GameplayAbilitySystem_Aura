// Copyright Hola Games


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddWeakLambda(this, [this](UAbilitySystemComponent* AbilitySystemComponent,
												const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
	{
		UAuraAbilitySystemComponent::EffectApplied(AbilitySystemComponent, EffectSpec, ActiveEffectHandle);
	});
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("Effect Applied"));
}
