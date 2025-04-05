#include "Character/PlayerGAS.h"
#include "Character/CharacterAttributeSet.h"

APlayerGAS::APlayerGAS()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void APlayerGAS::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitStats(UCharacterAttributeSet::StaticClass(), nullptr);
}

UAbilitySystemComponent* APlayerGAS::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
