#include "LavaPool.h"
#include "Interactive.h"
#include "./Character/CharacterAttributeSet.h"

ALavaPool::ALavaPool()
{
	/*PrimaryActorTick.bCanEverTick = true;*/

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
}

void ALavaPool::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALavaPool::OnOverlapBegin);
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ALavaPool::OnOverlapEnd);
	}
	
}

void ALavaPool::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
		ApplyPeriodicDamage(OtherActor);
}

void ALavaPool::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
		StopDamage(OtherActor);
}

void ALavaPool::ApplyPeriodicDamage(AActor* Actor)
{
    if (!Actor || ActiveDamageTimers.Contains(Actor))
        return;

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Actor]()
    {
        if (!Actor)
            return;

        UAbilitySystemComponent* Asc = Actor->FindComponentByClass<UAbilitySystemComponent>();
        if (Asc)
        {
            const UCharacterAttributeSet* Attributes = Asc->GetSet<UCharacterAttributeSet>();

            if (Attributes)
            {
                Asc->ApplyModToAttributeUnsafe(Attributes->GetHealthAttribute(), EGameplayModOp::Additive, -DamageAmount);

                UE_LOG(LogTemp, Warning, TEXT("Life after damage: %f"), Attributes->Health.GetCurrentValue());

                if (Attributes && Attributes->Health.GetCurrentValue() <= 0.0f)
                    Actor->Destroy();
            }
        }

    }, DamageInterval, true);

    ActiveDamageTimers.Add(Actor, TimerHandle);
}

void ALavaPool::StopDamage(AActor* Actor)
{
    if (ActiveDamageTimers.Contains(Actor))
    {
        GetWorld()->GetTimerManager().ClearTimer(ActiveDamageTimers[Actor]);
        ActiveDamageTimers.Remove(Actor);
    }
}

