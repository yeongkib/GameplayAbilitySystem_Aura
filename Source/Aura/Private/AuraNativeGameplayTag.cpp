// Copyright Hola Games


#include "AuraNativeGameplayTag.h"

FGameplayTag FAuraNativeGameplayTag::GetTag() const
{
    if (!InternalTag.IsValid())
    {
        InternalTag = FGameplayTag::RequestGameplayTag(TagName);
    }

    return InternalTag;
}

FName FAuraNativeGameplayTag::GetTagName() const
{
    return TagName;
}