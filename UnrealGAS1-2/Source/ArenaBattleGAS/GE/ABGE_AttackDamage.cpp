// Fill out your copyright notice in the Description page of Project Settings.


#include "GE/ABGE_AttackDamage.h"
#include "Attribute/ABCharacterAttributeSet.h"

UABGE_AttackDamage::UABGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo HealthModifier;
	//HealthModifier.Attribute = FGameplayAttribute(UABCharacterAttributeSet::GetHealthAttribute());
	HealthModifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(UABCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UABCharacterAttributeSet, Health)));
	HealthModifier.ModifierOp = EGameplayModOp::Additive;

	FScalableFloat DamageAmount(-10.f);
	FGameplayEffectModifierMagnitude ModMagnitude(DamageAmount);
	HealthModifier.ModifierMagnitude = ModMagnitude;
	Modifiers.Add(HealthModifier);
}
