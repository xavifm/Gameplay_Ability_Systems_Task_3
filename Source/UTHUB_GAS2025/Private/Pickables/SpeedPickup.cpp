#include "Pickables/SpeedPickup.h"
#include "Interactive.h"
#include "Character/CharacterAttributeSet.h"

ASpeedPickup::ASpeedPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpeedPickup::OnOverlapBegin);
}

void ASpeedPickup::BeginPlay()
{
    Super::BeginPlay();

}

void ASpeedPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        UAbilitySystemComponent* Asc = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
        if (Asc)
        {
            const UCharacterAttributeSet* Attributes = Cast<UCharacterAttributeSet>(Asc->GetAttributeSet(UCharacterAttributeSet::StaticClass()));
            if (Attributes)
            {
                Asc->ApplyModToAttributeUnsafe(Attributes->GetSpeedAttribute(), EGameplayModOp::Additive, SpeedAmount);
                UE_LOG(LogTemp, Warning, TEXT("Speed pickup: %f"), Attributes->Speed.GetCurrentValue());
                Destroy();
            }
        }
    }
}