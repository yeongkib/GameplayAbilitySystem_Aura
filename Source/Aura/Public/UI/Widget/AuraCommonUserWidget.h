// Copyright Hola Games

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "AuraCommonUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraCommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
