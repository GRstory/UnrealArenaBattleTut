// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_Jump.h"
#include "GameFramework/Character.h"
#include "GA/AT/ABAT_JumpAndWaitForLanding.h"

UABGA_Jump::UABGA_Jump()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UABGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!bResult)
	{
		return false;
	}
	
	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	return (Character && Character->CanJump());
}

void UABGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	/*UABAT_JumpAndWaitForLanding* LandingTask = UABAT_JumpAndWaitForLanding::CreateTask(this);
	LandingTask->OnComplete.AddDynamic(this, &UABGA_Jump::OnLandedCallback);
	LandingTask->ReadyForActivation();*/
}

void UABGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->StopJumping();
}

void UABGA_Jump::OnLandedCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}