// Copyright Hola Games


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();
 
    UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
 
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