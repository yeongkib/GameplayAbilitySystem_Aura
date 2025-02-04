// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class AURA_API FAuraNativeGameplayTag
{
public:
	FAuraNativeGameplayTag(FName InTagName, FName Comment = NAME_None) : TagName(InTagName){};

	operator FGameplayTag() const
	{
		return GetTag();
	}

	operator FName() const
	{
		return GetTagName();
	}

	FGameplayTag GetTag() const;
	FName GetTagName() const;

private:
	FName TagName;
	mutable FGameplayTag InternalTag;
};