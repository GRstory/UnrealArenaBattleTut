// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ABCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UABCharacterAttributeSet();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
};
