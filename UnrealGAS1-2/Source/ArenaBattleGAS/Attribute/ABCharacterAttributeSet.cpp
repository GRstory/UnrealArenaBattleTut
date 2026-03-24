// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/ABCharacterAttributeSet.h"

UABCharacterAttributeSet::UABCharacterAttributeSet() : AttackRange(100.0f), AttackRadius(50.f), AttackRate(30.f), MaxAttackRange(300.f), MaxAttackRadius(150.f), MaxAttackRate(100.f), MaxHealth(100.f)
{
	InitHealth(GetMaxHealth());
}

void UABCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UABCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}
