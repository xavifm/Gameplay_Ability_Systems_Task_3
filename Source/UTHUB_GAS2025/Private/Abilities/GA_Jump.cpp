#include "Abilities/GA_Jump.h"
#include "GameFramework/Character.h"

UGA_Jump::UGA_Jump()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Jump")));
}

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) 
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor)) 
    {
        Character->Jump();
        //animation
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
