// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ABGASUserWidget.h"
#include "GameplayEffectTypes.h"
#include "ABGASHPBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGASHPBarUserWidget : public UABGASUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void SetAbilitySystemComponent(AActor* Owner) override;
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnInvinsibleTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	void UpdateHpBar();

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UProgressBar> PbHpBar;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TxtHpStat;

	float MaxHealth = 0.1f;
	float CurrentHealth = 0.f;

	FLinearColor HpBarColor = FLinearColor::Red;
	FLinearColor HpBarInvincibleColor = FLinearColor::Black;
};
