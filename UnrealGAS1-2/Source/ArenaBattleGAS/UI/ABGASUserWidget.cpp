// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABGASUserWidget.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UABGASUserWidget::SetAbilitySystemComponent(AActor* Owner)
{
    if (Owner)
    {
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	}
}

UAbilitySystemComponent* UABGASUserWidget::GetAbilitySystemComponent() const
{
    return ASC;
}
