#include "Abilities/UGA_AttackBasic.h"
#include "Effects/GE_Damage_Basic.h"
#include "AbilitySystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameplayEffect.h"
#include "Character/CharacterAttributeSet.h"
#include <Character/PlayerGAS.h>

UUGA_AttackBasic::UUGA_AttackBasic()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Basic")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Attacking")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Defending")));
	DamageEffect = UGE_Damage_Basic::StaticClass();

}

void UUGA_AttackBasic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//apply effect and animation
	PerformAttackTrace();

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UUGA_AttackBasic::PerformAttackTrace()
{
	if (!CurrentActorInfo || !CurrentActorInfo->AvatarActor.IsValid()) return;

	AActor* Avatar = CurrentActorInfo->AvatarActor.Get();
	FVector Start = Avatar->GetActorLocation();
	FVector End = Start + Avatar->GetActorForwardVector() * 500.0f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Avatar);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params);

#if WITH_EDITOR
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);
#endif

	if (bHit && Hit.GetActor())
	{
		APlayerGAS* Target = Cast<APlayerGAS>(Hit.GetActor());
		if (Target)
		{
			UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
			UAbilitySystemComponent* SourceASC = CurrentActorInfo->AbilitySystemComponent.Get();

			if (TargetASC && SourceASC && DamageEffect)
			{
				FGameplayEffectContextHandle Context = SourceASC->MakeEffectContext();
				Context.AddSourceObject(Avatar);

				if (FGameplayEffectContext* RawContext = Context.Get())
					RawContext->AddInstigator(Avatar, Avatar);

				FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffect, GetAbilityLevel(), Context);

				if (SpecHandle.IsValid())
					TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

