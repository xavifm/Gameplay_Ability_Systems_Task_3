// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_AimTarget.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UGA_AimTarget : public UGameplayAbility
{
	GENERATED_BODY()

public:
    UGA_AimTarget();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;
	
    UFUNCTION()
    void OnReleasedEvent(FGameplayEventData Payload);

    void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
};
