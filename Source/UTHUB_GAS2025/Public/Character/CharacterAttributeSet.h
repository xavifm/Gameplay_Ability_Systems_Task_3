#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include <AbilitySystemComponent.h>
#include "CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class UTHUB_GAS2025_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCharacterAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Speed)

	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data);

private:
	const float BASE_HEALTH = 100;
	const float BASE_SPEED = 50;
};
