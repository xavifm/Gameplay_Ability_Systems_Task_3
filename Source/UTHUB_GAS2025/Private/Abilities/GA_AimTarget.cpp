#include "Abilities/GA_AimTarget.h"
#include <Abilities/Tasks/AbilityTask_WaitGameplayEvent.h>

UGA_AimTarget::UGA_AimTarget()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Aim")));
    ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Aiming")));
    ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Defending")));
}

void UGA_AimTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("Aiming!"));

    UAbilityTask_WaitGameplayEvent* WaitEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag("Input.Release.Aim"));
    if (WaitEvent)
    {
        WaitEvent->EventReceived.AddDynamic(this, &UGA_AimTarget::OnReleasedEvent);
        WaitEvent->ReadyForActivation();
    }
}

void UGA_AimTarget::OnReleasedEvent(FGameplayEventData Payload)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGA_AimTarget::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    UE_LOG(LogTemp, Warning, TEXT("Aiming mode stopped!"));
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
