// Copyright Hola Games

#include "AuraGameplayTags.h"

#define DEFINE_GAMEPLAY_TAG(AttributeType, AttributeName, Comment) \
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_##AttributeType##_##AttributeName, *FString((FString("Attributes.") + #AttributeType + FString(".") + #AttributeName)), Comment)
	
	DEFINE_GAMEPLAY_TAG(Vital, Health, "Amount of damage a player can take before death");
	DEFINE_GAMEPLAY_TAG(Vital, Mana, "A resource used to cast spells");

	DEFINE_GAMEPLAY_TAG(Primary, Strength, "Increases physical damage");
	DEFINE_GAMEPLAY_TAG(Primary, Intelligence, "Increases magical damage");
	DEFINE_GAMEPLAY_TAG(Primary, Resilience, "Increases Armor and Armor Penetration");
	DEFINE_GAMEPLAY_TAG(Primary, Vigor, "Increases Health");

	DEFINE_GAMEPLAY_TAG(Secondary, Armor, "Reduces damage taken, improves Block Chance");
	DEFINE_GAMEPLAY_TAG(Secondary, ArmorPenetration, "Ignores Percentage of enemy Armor, increases Critical Hit Chance");
	DEFINE_GAMEPLAY_TAG(Secondary, BlockChance, "Chance to cut incoming damage in half");
	DEFINE_GAMEPLAY_TAG(Secondary, CriticalHitChance, "Chance to double damage plus critical hit bonus");
	DEFINE_GAMEPLAY_TAG(Secondary, CriticalHitDamage, "Bonus damage added when a critical hit is scored");
	DEFINE_GAMEPLAY_TAG(Secondary, CriticalHitResistance, "Reduces Critical Hit Chance of attacking enemies");
	DEFINE_GAMEPLAY_TAG(Secondary, HealthRegeneration, "Amount of Health regenerated every 1 second");
	DEFINE_GAMEPLAY_TAG(Secondary, ManaRegeneration, "Amount of Mana regenerated every 1 second");
	DEFINE_GAMEPLAY_TAG(Secondary, MaxHealth, "Maximum amount of Health obtainable");
	DEFINE_GAMEPLAY_TAG(Secondary, MaxMana, "Maximum amount of Mana obtainable");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Resistance, "Attributes.Resistance", "Resistance Attributes")
	DEFINE_GAMEPLAY_TAG(Resistance, FireResistance, "Resistance to Fire damage");
	DEFINE_GAMEPLAY_TAG(Resistance, LightningResistance, "Resistance to Lightning damage");
	DEFINE_GAMEPLAY_TAG(Resistance, ArcaneResistance, "Resistance to Arcane damage");
	DEFINE_GAMEPLAY_TAG(Resistance, PhysicalResistance, "Resistance to physical damage");

#undef DEFINE_GAMEPLAY_TAG

UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_LMB, "InputTag.LMB", "Input Tag for Left Mouse Button")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_RMB, "InputTag.RMB", "Input Tag for Right Mouse Button")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_1, "InputTag.1", "Input Tag for 1 key")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_2, "InputTag.2", "Input Tag for 2 key")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_3, "InputTag.3", "Input Tag for 3 key")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_4, "InputTag.4", "Input Tag for 4 key")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Damage, "Damage", "Damage")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Damage_Fire, "Damage.Fire", "Fire Damage Type")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Damage_Lightning, "Damage.Lightning", "Lightning Damage Type")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Damage_Arcane, "Damage.Arcane", "Arcane Damage Type")
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Damage_Physical, "Damage.Physical", "Physical Damage Type")

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effects_HitReact, "Effects.HitReact", "Tag granted when Hit Reacting")

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
FGameplayTagContainer FAuraGameplayTags::DamageTypes;
FGameplayTagContainer FAuraGameplayTags::ResistanceTypes;
bool FAuraGameplayTags::bIsInitialized = false;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
#define ADD_TAG_TO_CONTAINER(AttributeType, AttributeName) \
	GameplayTags.TagContainer.AddTag(Attributes_##AttributeType##_##AttributeName);

	ADD_TAG_TO_CONTAINER(Vital, Health);
	ADD_TAG_TO_CONTAINER(Vital, Mana);

	ADD_TAG_TO_CONTAINER(Primary, Strength);
	ADD_TAG_TO_CONTAINER(Primary, Intelligence);
	ADD_TAG_TO_CONTAINER(Primary, Resilience);
	ADD_TAG_TO_CONTAINER(Primary, Vigor);

	ADD_TAG_TO_CONTAINER(Secondary, Armor);
	ADD_TAG_TO_CONTAINER(Secondary, ArmorPenetration);
	ADD_TAG_TO_CONTAINER(Secondary, BlockChance);
	ADD_TAG_TO_CONTAINER(Secondary, CriticalHitChance);
	ADD_TAG_TO_CONTAINER(Secondary, CriticalHitDamage);
	ADD_TAG_TO_CONTAINER(Secondary, CriticalHitResistance);
	ADD_TAG_TO_CONTAINER(Secondary, HealthRegeneration);
	ADD_TAG_TO_CONTAINER(Secondary, ManaRegeneration);
	ADD_TAG_TO_CONTAINER(Secondary, MaxHealth);
	ADD_TAG_TO_CONTAINER(Secondary, MaxMana);

	ADD_TAG_TO_CONTAINER(Resistance, FireResistance);
	ADD_TAG_TO_CONTAINER(Resistance, LightningResistance);
	ADD_TAG_TO_CONTAINER(Resistance, ArcaneResistance);
	ADD_TAG_TO_CONTAINER(Resistance, PhysicalResistance);

#undef ADD_TAG_TO_CONTAINER

	DamageTypes = UGameplayTagsManager::Get().RequestGameplayTagChildren(Tag_Damage);
	ResistanceTypes = UGameplayTagsManager::Get().RequestGameplayTagChildren(Attributes_Resistance);

	bIsInitialized = true;
}

FGameplayTag FAuraGameplayTags::FindTagByString(const FString& TagString, bool bMatchPartialString)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

	if (!Tag.IsValid() && bMatchPartialString)
	{
		FGameplayTagContainer AllTags;
		Manager.RequestAllGameplayTags(AllTags, true);

		for (const FGameplayTag& TestTag : AllTags)
		{
			if (TestTag.ToString().Contains(TagString))
			{
				UE_LOG(LogTemp, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
				Tag = TestTag;
				break;
			}
		}
	}

	return Tag;
}
