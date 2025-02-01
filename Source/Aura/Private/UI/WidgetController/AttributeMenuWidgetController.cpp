// Copyright Hola Games

#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	for (const FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeToGet).AddWeakLambda(
			this, [this, &Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info);
			});
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	for (const FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FAuraAttributeInfo& Info) const
{
	// Getting info from DataAsset AttributeInfo based on the GameplayTag
	FAuraAttributeInfo NewInfo = Info;
	// Set the hidden attribute value in AttributeInfo DataAsset
	NewInfo.AttributeValue = Info.AttributeToGet.GetNumericValue(AttributeSet);
	// Broadcast for those who subscribe. IE the attribute menu widget in blueprint
	AttributeInfoDelegate.Broadcast(NewInfo);
}