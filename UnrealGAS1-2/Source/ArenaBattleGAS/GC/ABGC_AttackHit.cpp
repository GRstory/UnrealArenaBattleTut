// Fill out your copyright notice in the Description page of Project Settings.


#include "GC/ABGC_AttackHit.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

UABGC_AttackHit::UABGC_AttackHit()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (HitParticleRef.Object)
	{
		HitParticle = HitParticleRef.Object;
	}
}

bool UABGC_AttackHit::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (HitResult)
	{
		UGameplayStatics::SpawnEmitterAtLocation(MyTarget->GetWorld(), HitParticle, HitResult->ImpactPoint, FRotator::ZeroRotator, true);
	}
	return false;
}
