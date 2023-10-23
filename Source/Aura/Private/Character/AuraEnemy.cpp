// Copyright Hola Games


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();
 
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
 
    GetMesh()->OnBeginCursorOver.AddDynamic(this, &AAuraEnemy::OnMouseOver);
    GetMesh()->OnEndCursorOver.AddDynamic(this,&AAuraEnemy::OnMouseOut);
}
 
void AAuraEnemy::OnMouseOver(UPrimitiveComponent* TouchedComponent)
{
    HighlightActor();
}
 
void AAuraEnemy::OnMouseOut(UPrimitiveComponent* TouchedComponent)
{
    UnHighlightActor();
}
 
void AAuraEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    Weapon->SetRenderCustomDepth(true);
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}
 
void AAuraEnemy::UnHighlightActor()
{
    GetMesh()->SetRenderCustomDepth(false);
    Weapon->SetRenderCustomDepth(false);
}