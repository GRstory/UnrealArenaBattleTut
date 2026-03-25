// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/ABCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ArenaBattleGAS.h"
#include "Tag/ABGameplayTag.h"

UABCharacterAttributeSet::UABCharacterAttributeSet() : AttackRange(100.0f), AttackRadius(50.f), AttackRate(30.f), MaxAttackRange(300.f), MaxAttackRadius(150.f), MaxAttackRate(100.f), MaxHealth(100.f), Damage(0.f)
{
	InitHealth(GetMaxHealth());
}

void UABCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	/*if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}*/

	if(Attribute == GetDamageAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, NewValue);
	}
}

bool UABCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if(!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}
	if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude > 0.f && Data.Target.HasMatchingGameplayTag(ABTAG_CHARACTER_INVINCIBLE))
		{
			Data.EvaluatedData.Magnitude = 0.f;
			false;
		}
	}

	return true;
}

void UABCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.f;
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		ABGAS_LOG(LogABGAS, Warning, TEXT("Direct Health Attribute Execute, %f"), GetHealth());
		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
	}
	else if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		ABGAS_LOG(LogABGAS, Log, TEXT("Damage, %f"), GetDamage());
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.f);
	}

	if ((GetHealth() <= MinimumHealth) && !bOutOfHealth)
	{
		Data.Target.AddLooseGameplayTag(ABTAG_CHARACTER_DEAD);
		OnOutOfHealth.Broadcast();
		bOutOfHealth = true;
	}
}
