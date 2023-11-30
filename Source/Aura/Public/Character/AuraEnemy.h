// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include <Character/AuraCharacterBase.h>
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void BeginPlay() override;

#pragma region Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UFUNCTION()
	void OnMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnMouseOut(UPrimitiveComponent* TouchedComponent);
#pragma endregion
	virtual int32 GetActorLevel() override;
#pragma region Combat Interface
	
#pragma endregion

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
