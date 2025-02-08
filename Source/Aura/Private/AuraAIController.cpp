// Copyright Hola Games


#include "AuraAIController.h"

AAuraAIController::AAuraAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetGenericTeamId(FGenericTeamId(2));
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>("StateTreeAIComponent");
}