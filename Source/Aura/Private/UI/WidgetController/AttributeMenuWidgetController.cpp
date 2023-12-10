// Copyright Hola Games

#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	for (const auto& [Tag, Info] : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeToGet).AddWeakLambda(
			this, [this, &Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info.AttributeTag);
			});
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	for (const auto& [Tag, Info] : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info.AttributeTag);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag) const
{
	check(AttributeInfo);

	// Getting info from DataAsset AttributeInfo based on the GameplayTag
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	// Set the hidden attribute value in AttributeInfo DataAsset
	Info.AttributeValue = Info.AttributeToGet.GetNumericValue(AttributeSet);
	// Broadcast for those who subscribe. IE the attribute menu widget in blueprint
	AttributeInfoDelegate.Broadcast(Info);
}