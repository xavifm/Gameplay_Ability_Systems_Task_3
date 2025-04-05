#include "Pickables/HealthPickup.h"
#include "Interactive.h"
#include "Character/CharacterAttributeSet.h"

AHealthPickup::AHealthPickup()
{
	PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);
}

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        UAbilitySystemComponent* Asc = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
        if (Asc)
        {
            const UCharacterAttributeSet* Attributes = Cast<UCharacterAttributeSet>(Asc->GetAttributeSet(UCharacterAttributeSet::StaticClass()));
            if (Attributes)
            {
                Asc->ApplyModToAttributeUnsafe(Attributes->GetHealthAttribute(), EGameplayModOp::Additive, HealAmount);
                UE_LOG(LogTemp, Warning, TEXT("Life pickup: %f"), Attributes->Health.GetCurrentValue());
                Destroy();
            }
        }
    }
}

