// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABGASWidgetComponent.h"
#include "UI/ABGASUserWidget.h"

void UABGASWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UABGASUserWidget* ABGASWidget = Cast<UABGASUserWidget>(GetWidget());
	if (ABGASWidget)
	{
		ABGASWidget->SetAbilitySystemComponent(GetOwner());
	}
}
