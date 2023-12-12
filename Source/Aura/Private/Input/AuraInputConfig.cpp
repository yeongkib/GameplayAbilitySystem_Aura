// Copyright Hola Games


#include "Input/AuraInputConfig.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"

EDataValidationResult FAuraInputAction::IsDataValid(FDataValidationContext& Context, const int Index) const
{
	EDataValidationResult Result = EDataValidationResult::Valid;

	if (InputAction == nullptr)
	{
		Result = EDataValidationResult::Invalid;
		const FText ErrorMessage = FText::FromString(FString::Printf(TEXT("\n\nA InputAction at index [%i] is none but has never to be none!"
			"\nPlease set a valid class or delete the index entry in the Ability Input Actions Array."), Index));
		Context.AddError(ErrorMessage);
	}
	
	if (!InputTag.IsValid())
	{
		Result = EDataValidationResult::Invalid;
		const FText ErrorMessage = FText::FromString(FString::Printf(TEXT("\n\nA InputTag at index [%i] is not valid!"
			"\nPlease set a valid tag or delete the index entry in the Ability Input Actions Array."), Index));
		Context.AddError(ErrorMessage);
	}
	
	return Result;
}

EDataValidationResult UAuraInputConfig::IsDataValid(FDataValidationContext& Context, const int Index) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	for (int32 i = 0; i < AbilityInputAction.Num(); ++i)
	{
		Result = CombineDataValidationResults(Result, AbilityInputAction[i].IsDataValid(Context, i));
	}
	
	return Result;
}
#endif

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputAction)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
