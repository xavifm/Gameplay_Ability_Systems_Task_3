#include "Character/CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
    Health.SetBaseValue(BASE_HEALTH);
    Health.SetCurrentValue(BASE_HEALTH);

    Speed.SetBaseValue(BASE_SPEED);
    Speed.SetCurrentValue(BASE_SPEED);
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float NewHealth = FMath::Clamp(Health.GetCurrentValue(), 0.f, BASE_HEALTH);
		Health.SetCurrentValue(NewHealth);


		AActor* Instigator = Data.EffectSpec.GetContext().GetInstigator();

		if (Instigator)
		{
			UE_LOG(LogTemp, Log, TEXT("Damage: %.2f"), NewHealth);
		}
	}
}
