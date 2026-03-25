// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABGASHPBarUserWidget.h"
#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Tag/ABGameplayTag.h"

void UABGASHPBarUserWidget::SetAbilitySystemComponent(AActor* Owner)
{
	Super::SetAbilitySystemComponent(Owner);
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UABCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &UABGASHPBarUserWidget::OnHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UABCharacterAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UABGASHPBarUserWidget::OnMaxHealthChanged);
		ASC->RegisterGameplayTagEvent(ABTAG_CHARACTER_INVINCIBLE, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UABGASHPBarUserWidget::OnInvinsibleTagChanged);
		PbHpBar->SetFillColorAndOpacity(HpBarColor);

		const UABCharacterAttributeSet* AttributeSet = ASC->GetSet<UABCharacterAttributeSet>();
		if(AttributeSet)
		{
			MaxHealth = AttributeSet->GetMaxHealth();
			CurrentHealth = AttributeSet->GetHealth();

			if (MaxHealth > 0.f)
			{
				UpdateHpBar();
			}
		}
	}
}

void UABGASHPBarUserWidget::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	MaxHealth = Data.NewValue;

	UpdateHpBar();
}

void UABGASHPBarUserWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	CurrentHealth = Data.NewValue;

	UpdateHpBar();
}

void UABGASHPBarUserWidget::OnInvinsibleTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		PbHpBar->SetFillColorAndOpacity(HpBarInvincibleColor);
		PbHpBar->SetPercent(1.f);
	}
	else
	{
		PbHpBar->SetFillColorAndOpacity(HpBarColor);
		UpdateHpBar();
	}
}

void UABGASHPBarUserWidget::UpdateHpBar()
{
	if (PbHpBar)
	{
		PbHpBar->SetPercent(CurrentHealth / MaxHealth);
	}

	if(TxtHpStat)
	{
		FString HpStat = FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth);
		TxtHpStat->SetText(FText::FromString(HpStat));
	}
}
