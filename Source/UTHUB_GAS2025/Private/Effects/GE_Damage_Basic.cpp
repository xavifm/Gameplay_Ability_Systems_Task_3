#include "Effects/GE_Damage_Basic.h"
#include "Character/CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

UGE_Damage_Basic::UGE_Damage_Basic()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo DamageModifier;
	DamageModifier.Attribute = FGameplayAttribute(UCharacterAttributeSet::GetHealthAttribute());
	DamageModifier.ModifierOp = EGameplayModOp::Additive;
	DamageModifier.ModifierMagnitude = FScalableFloat(-20.0f);

	Modifiers.Add(DamageModifier);
}