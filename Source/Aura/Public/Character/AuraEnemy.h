// Copyright Hola Games

#pragma once


#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include <Character/AuraCharacterBase.h>

#include "GenericTeamAgentInterface.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

#pragma region Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UFUNCTION()
	void OnMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseOut(UPrimitiveComponent* TouchedComponent);
#pragma endregion

#pragma region Combat Interface
	virtual int32 GetActorLevel() override;
	virtual void Die() override;
#pragma endregion

#pragma region IGenericTeamAgentInterface
public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { /** Do Nothing */};
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
 
private:
	FGenericTeamId TeamId;
#pragma endregion

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
