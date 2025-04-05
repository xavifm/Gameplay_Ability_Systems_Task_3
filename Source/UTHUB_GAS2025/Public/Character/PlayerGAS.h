#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AttributeSet.h>
#include "PlayerGAS.generated.h"

UCLASS()
class UTHUB_GAS2025_API APlayerGAS : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerGAS();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAttributeSet* Attributes;
	
	UAbilitySystemComponent* GetAbilitySystemComponent() const;

protected:
	virtual void BeginPlay() override;



};
