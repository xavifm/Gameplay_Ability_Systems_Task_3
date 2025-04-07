#include "Abilities/GA_Defend.h"
#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include <Abilities/Tasks/AbilityTask_WaitGameplayEvent.h>

UGA_Defend::UGA_Defend()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Defend")));
    ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Defending")));
    ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Attacking")));
}

void UGA_Defend::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (DefendMontage && ActorInfo->AvatarActor.IsValid())
    {
        ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
        if (Character && Character->GetMesh())
        {
            Character->PlayAnimMontage(DefendMontage);
        }
    }

    UAbilityTask_WaitGameplayEvent* WaitEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag("Input.Release.Defend"));
    if(WaitEvent) 
    {
        WaitEvent->EventReceived.AddDynamic(this, &UGA_Defend::OnReleasedEvent);
        WaitEvent->ReadyForActivation();
    }

}

void UGA_Defend::OnReleasedEvent(FGameplayEventData Payload)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGA_Defend::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (DefendMontage && ActorInfo->AvatarActor.IsValid())
    {
        ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
        if (Character && Character->GetMesh())
        {
            Character->StopAnimMontage(DefendMontage);
        }
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


