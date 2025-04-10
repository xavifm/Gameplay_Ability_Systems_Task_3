#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UGA_AttackBasic.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UUGA_AttackBasic : public UGameplayAbility
{
	GENERATED_BODY()

public:
    UUGA_AttackBasic();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;
	
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TSubclassOf<UGameplayEffect> DamageEffect;

    void PerformAttackTrace();

};
