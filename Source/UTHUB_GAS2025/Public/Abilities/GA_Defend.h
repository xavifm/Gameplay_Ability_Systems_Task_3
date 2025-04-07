#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Defend.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UGA_Defend : public UGameplayAbility
{
	GENERATED_BODY()

public:
    UGA_Defend();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;
    
    UFUNCTION()
    void OnReleasedEvent(FGameplayEventData Payload);
    
    void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Animation")
    UAnimMontage* DefendMontage;
};
