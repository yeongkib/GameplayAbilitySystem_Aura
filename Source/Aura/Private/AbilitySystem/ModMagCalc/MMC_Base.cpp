// Copyright Hola Games


#include "AbilitySystem/ModMagCalc/MMC_Base.h"

#include "Interaction/CombatInterface.h"

float UMMC_Base::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
    
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 ActorLevel = CombatInterface->GetActorLevel();
 
	float AttributeContribution = 0.f;
    
	for (FAttributeCoefficient AttributeCoefficient : AttributeCoefficients)
	{
		if (const FGameplayEffectAttributeCaptureDefinition* CapturedAttribute = RelevantAttributesToCapture.
		   FindByPredicate([AttributeCoefficient](const FGameplayEffectAttributeCaptureDefinition& Item)
		   {
			  return Item.AttributeToCapture.AttributeName == AttributeCoefficient.Attribute.AttributeName;
		   }))
		{
			float AttributeValue = 0.f;
			GetCapturedAttributeMagnitude(*CapturedAttribute, Spec, EvaluationParameters, AttributeValue);
			AttributeValue = FMath::Max<float>(AttributeValue, 0.f);
			switch (AttributeCoefficient.Operation)
			{
			case EGameplayModOp::Additive:AttributeContribution += (AttributeCoefficient.Coefficient + AttributeValue); break;
			case EGameplayModOp::Multiplicitive:AttributeContribution += (AttributeCoefficient.Coefficient * AttributeValue); break;
			case EGameplayModOp::Division:AttributeContribution += (AttributeCoefficient.Coefficient / AttributeValue); break;
			default: ;
			}
		}
	}
 
	// BaseValue + Coeff1 * Att1 ... + LevelMult * ActorLevel
	return BaseValue + AttributeContribution + LevelMultiplier * ActorLevel;
}
