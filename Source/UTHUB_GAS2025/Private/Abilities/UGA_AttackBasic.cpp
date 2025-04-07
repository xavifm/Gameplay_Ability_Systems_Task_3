// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/UGA_AttackBasic.h"

UUGA_AttackBasic::UUGA_AttackBasic()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Basic")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Attacking")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Defending")));

}

void UUGA_AttackBasic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//apply effect and animation

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
