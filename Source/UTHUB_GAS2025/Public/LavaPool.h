#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "LavaPool.generated.h"

UCLASS()
class UTHUB_GAS2025_API ALavaPool : public AActor
{
	GENERATED_BODY()
	
public:	
	ALavaPool();

protected:
	virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere, Category = "Lava Settings")
    float DamageAmount = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Lava Settings")
    float DamageInterval = 1.0f;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void ApplyPeriodicDamage(AActor* Actor);
    void StopDamage(AActor* Actor);

    TMap<AActor*, FTimerHandle> ActiveDamageTimers;

};
