// Copyright Hola Games


#include "UI/HUD/AuraHud.h"
#include "UI/Widget/AuraCommonUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UAuraCommonUserWidget* Widget = CreateWidget<UAuraCommonUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
