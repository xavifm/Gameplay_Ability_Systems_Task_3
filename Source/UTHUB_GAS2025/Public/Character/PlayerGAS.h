#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <AttributeSet.h>
#include <EnhancedInputSubsystems.h>
#include "PlayerGAS.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	Aim		   UMETA(DisplayName = "Aim"),
	Attack     UMETA(DisplayName = "Attack"),
	Defend     UMETA(DisplayName = "Defend"),
	Jump	   UMETA(DisplayName = "Jump")
};


UCLASS()
class UTHUB_GAS2025_API APlayerGAS : public ACharacter
{
	GENERATED_BODY()
	
public:	
	APlayerGAS();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAttributeSet* Attributes;
	
	UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* attackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* defendAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* aimAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* jumpAction;

	UFUNCTION()
	void OnAttackPressed();

	UFUNCTION()
	void OnDefendPressed();

	UFUNCTION()
	void OnDefendReleased();

	UFUNCTION()
	void OnAimPressed();

	UFUNCTION()
	void OnAimReleased();

	UFUNCTION()
	void OnJumpPressed();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

protected:
	virtual void BeginPlay() override;
	void InitializeAbilities();
};
