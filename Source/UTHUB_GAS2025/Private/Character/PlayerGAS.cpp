#include "Character/PlayerGAS.h"
#include "Character/CharacterAttributeSet.h"
#include "Abilities/GA_Defend.h"
#include "Abilities/UGA_AttackBasic.h"
#include "Abilities/GA_Jump.h"
#include "Abilities/GA_AimTarget.h"
#include <EnhancedInputComponent.h>


APlayerGAS::APlayerGAS()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attributes = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("Attributes"));
}

void APlayerGAS::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitStats(UCharacterAttributeSet::StaticClass(), nullptr);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	InitializeAbilities();
}

void APlayerGAS::OnAttackPressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Attack));
	}
}

void APlayerGAS::OnDefendPressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Defend));
	}
}

void APlayerGAS::OnDefendReleased()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag("Input.Release.Defend");
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (ASC)
	{
		ASC->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

void APlayerGAS::OnAimPressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Aim));
	}
}

void APlayerGAS::OnAimReleased()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag("Input.Release.Aim");
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (ASC)
	{
		ASC->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

void APlayerGAS::OnJumpPressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Jump));
	}
}

void APlayerGAS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->bBlockInput = false;

		if (attackAction)
			EnhancedInput->BindAction(attackAction, ETriggerEvent::Started, this, &APlayerGAS::OnAttackPressed);

		if (defendAction) 
		{
			EnhancedInput->BindAction(defendAction, ETriggerEvent::Started, this, &APlayerGAS::OnDefendPressed);
			EnhancedInput->BindAction(defendAction, ETriggerEvent::Completed, this, &APlayerGAS::OnDefendReleased);
		}

		if (aimAction) 
		{
			EnhancedInput->BindAction(aimAction, ETriggerEvent::Started, this, &APlayerGAS::OnAimPressed);
			EnhancedInput->BindAction(aimAction, ETriggerEvent::Completed, this, &APlayerGAS::OnAimReleased);
		}

		if (jumpAction)
			EnhancedInput->BindAction(jumpAction, ETriggerEvent::Started, this, &APlayerGAS::OnJumpPressed);
	}
}


void APlayerGAS::InitializeAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent) return;

	TArray<TPair<TSubclassOf<UGameplayAbility>, EAbilityInputID>> AbilitiesToGive = {
		{UGA_Defend::StaticClass(), EAbilityInputID::Defend},
		{UUGA_AttackBasic::StaticClass(), EAbilityInputID::Attack},
		{UGA_AimTarget::StaticClass(), EAbilityInputID::Aim},
		{UGA_Jump::StaticClass(), EAbilityInputID::Jump},
	};

	for (const auto& Pair : AbilitiesToGive)
	{
		const TSubclassOf<UGameplayAbility> AbilityClass = Pair.Key;
		const EAbilityInputID InputID = Pair.Value;

		if (*AbilityClass)
		{
			FGameplayAbilitySpec Spec(AbilityClass, 1, static_cast<int32>(InputID), this);
			AbilitySystemComponent->GiveAbility(Spec);
		}
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* APlayerGAS::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
