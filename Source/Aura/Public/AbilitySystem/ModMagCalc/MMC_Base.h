// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Base.generated.h"

USTRUCT(BlueprintType)
struct FAttributeCoefficient
{
	GENERATED_BODY()
	FAttributeCoefficient() {}
    
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Coefficient = 1.f;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ValidEnumValues="Additive, Multiplicitive, Division") )
	TEnumAsByte<EGameplayModOp::Type> Operation = EGameplayModOp::Additive;
};

/**
 * 
 */
UCLASS()
class AURA_API UMMC_Base : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float BaseValue = 1.f;

	// Coefficients matching captured definitions 1 for 1.
	UPROPERTY(EditAnywhere)
	TArray<FAttributeCoefficient> AttributeCoefficients;
 
	UPROPERTY(EditAnywhere)
	float LevelMultiplier = 10.f;

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
