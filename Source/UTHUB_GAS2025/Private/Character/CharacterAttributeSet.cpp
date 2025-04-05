#include "Character/CharacterAttributeSet.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
    Health.SetBaseValue(BASE_HEALTH);
    Health.SetCurrentValue(BASE_HEALTH);

    Speed.SetBaseValue(BASE_SPEED);
    Speed.SetCurrentValue(BASE_SPEED);
}
