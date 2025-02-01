// Copyright Hola Games

#include "AbilitySystem/Data/AttributeInfo.h"

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/AuraAttributeSet.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}

void UAttributeInfo::PostLoad()
{
	Super::PostLoad();
#if WITH_EDITOR
	PopulateDataAsset();
#endif
}

#if WITH_EDITOR
void UAttributeInfo::PopulateDataAsset()
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	AttributeInformation.Empty();
	AttributeInformation.SetNumZeroed(GameplayTags.TagContainer.Num());

	for (int32 i = 0; i < GameplayTags.TagContainer.Num(); ++i)
	{
		const FGameplayTag IndexTag = GameplayTags.TagContainer.GetByIndex(i);
		const FGameplayTagNode* TagNode = UGameplayTagsManager::Get().FindTagNode(IndexTag).Get(); // Get the last node of the GameplayTag
		FString NodeString = FName::NameToDisplayString(TagNode->GetSimpleTagName().ToString(), false); // Get node name (i.e. Attribute.Primary.Strength return Strength) and make it display ready
		AttributeInformation[i].AttributeTag = IndexTag;
		AttributeInformation[i].AttributeName = FText::FromString(NodeString); // Set AttributeName

		// Set AttributeToGet
		for (TFieldIterator<FProperty> It(UAuraAttributeSet::StaticClass()); It; ++It)
		{
			if (FGameplayAttribute::IsGameplayAttributeDataProperty(*It) && FGameplayAttribute(*It).GetName() == TagNode->GetSimpleTagName().ToString())
			{
				AttributeInformation[i].AttributeToGet = FGameplayAttribute(*It);
				break;
			}
		}

		const FName TagName = IndexTag.GetTagName();
		OUT FString TagComment;
		OUT FName TagSource;
		OUT bool bIsTagExplicit = false;
		OUT bool bIsRestrictedTag= false;
		OUT bool bAllowNonRestrictedChildren = false;
		UGameplayTagsManager::Get().GetTagEditorData(TagName, TagComment, TagSource, bIsTagExplicit, bIsRestrictedTag, bAllowNonRestrictedChildren);
		AttributeInformation[i].AttributeDescription = FText::FromString(TagComment); // Set AttributeDescription
	}
}
#endif
