// Copyright Hola Games


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraCommonUserWidget.h"

AAuraEnemy::AAuraEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

    HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
    HealthBar->SetupAttachment(GetRootComponent());
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();
    InitAbilityActorInfo();
    
    GetMesh()->OnBeginCursorOver.AddDynamic(this, &AAuraEnemy::OnMouseOver);
    GetMesh()->OnEndCursorOver.AddDynamic(this,&AAuraEnemy::OnMouseOut);

    if (UAuraCommonUserWidget* AuraCommonUserWidget = Cast<UAuraCommonUserWidget>(HealthBar->GetUserWidgetObject()))
    {
        AuraCommonUserWidget->SetWidgetController(this);
    }
    
    if (const UAuraAttributeSet* AuraAs = Cast<UAuraAttributeSet>(AttributeSet))
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAs->GetHealthAttribute()).AddLambda(
            [this](const FOnAttributeChangeData& Data)
            {
                OnHealthChanged.Broadcast(Data.NewValue);
            });
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAs->GetMaxHealthAttribute()).AddLambda(
            [this](const FOnAttributeChangeData& Data)
            {
                OnMaxHealthChanged.Broadcast(Data.NewValue);
            });

        OnHealthChanged.Broadcast(AuraAs->GetHealth());
        OnMaxHealthChanged.Broadcast(AuraAs->GetMaxHealth());
    }
}
 
void AAuraEnemy::OnMouseOver(UPrimitiveComponent* TouchedComponent)
{
    HighlightActor();
}
 
void AAuraEnemy::OnMouseOut(UPrimitiveComponent* TouchedComponent)
{
    UnHighlightActor();
}

int32 AAuraEnemy::GetActorLevel()
{
    return Level;
}

void AAuraEnemy::InitAbilityActorInfo()
{
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

    InitializeDefaultAttributes();
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
    UAuraAbilitySystemLibrary::InitializedDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
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