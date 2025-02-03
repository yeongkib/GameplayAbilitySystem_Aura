// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/StateTreeAIComponent.h"
#include "AuraAIController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAuraAIController();

protected:

	UPROPERTY()
	TObjectPtr<UStateTreeAIComponent> StateTreeComponent;
};
