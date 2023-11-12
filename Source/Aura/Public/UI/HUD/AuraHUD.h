// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraCommonUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	TObjectPtr<UAuraCommonUserWidget> OverlayWidgets;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraCommonUserWidget> OverlayWidgetClass;
};
