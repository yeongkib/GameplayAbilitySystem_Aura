// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

struct FGameplayTag;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

#if WITH_EDITOR
	// Validation check if all properties are set correct
	EDataValidationResult IsDataValid(FDataValidationContext& Context, const int Index) const;
#endif
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	// Validation check if GameplayEffectClass is not empty
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputAction;
};
