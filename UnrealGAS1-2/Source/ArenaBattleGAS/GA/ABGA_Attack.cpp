// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_Attack.h"
#include "Character/ABCharacterBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/ABComboActionData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ArenaBattleGAS.h"

UABGA_Attack::UABGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AABCharacterBase* CharacterBase = CastChecked<AABCharacterBase>(ActorInfo->AvatarActor.Get());
	CurrentComboActionData = CharacterBase->GetComboActionData();

	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), CharacterBase->GetComboActionMontage(), 1.0f, GetNextSection());
	if (PlayAttackTask)
	{
		PlayAttackTask->OnCompleted.AddDynamic(this, &UABGA_Attack::OnCompleteCallback);
		PlayAttackTask->OnInterrupted.AddDynamic(this, &UABGA_Attack::OnInterruptedCallback);
		PlayAttackTask->ReadyForActivation();

		StartComboTimer();
	}
}

void UABGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);


}

void UABGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AABCharacterBase* CharacterBase = CastChecked<AABCharacterBase>(ActorInfo->AvatarActor.Get());
	if (CharacterBase)
	{
		CharacterBase->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		CurrentComboActionData = nullptr;
		CurrentCombo = 0;
		HasNextComboInput = false;
	}
}

void UABGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	ABGAS_LOG(LogABGAS, Log, TEXT("Input Pressed"));
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboInput = false;
	}
	else
	{
		HasNextComboInput = true;
	}
}

void UABGA_Attack::OnCompleteCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UABGA_Attack::OnInterruptedCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FName UABGA_Attack::GetNextSection()
{
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, CurrentComboActionData->MaxComboCount);
	FName NextSectionName = *FString::Printf(TEXT("%s%d"), *CurrentComboActionData->MontageSectionNamePrefix, CurrentCombo);
	return NextSectionName;
}

void UABGA_Attack::StartComboTimer()
{
	int32 ComboIdx = CurrentCombo - 1;
	ensure(CurrentComboActionData->EffectiveFrameCount.IsValidIndex(ComboIdx));

	const float ComboEffectiveTime = CurrentComboActionData->EffectiveFrameCount[ComboIdx] / CurrentComboActionData->FrameRate;
	if (ComboEffectiveTime > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &UABGA_Attack::CheckComboInput, ComboEffectiveTime, false);
	}
}

void UABGA_Attack::CheckComboInput()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboInput)
	{
		MontageJumpToSection(GetNextSection());
		StartComboTimer();
		HasNextComboInput = false;
	}
}
