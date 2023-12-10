// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Health);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Mana);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Resilience);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BlockChance);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana);

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct AURA_API FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	static FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString);

	FGameplayTagContainer TagContainer = FGameplayTagContainer();
private:
	static FAuraGameplayTags GameplayTags;
};