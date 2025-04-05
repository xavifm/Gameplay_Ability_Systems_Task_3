// Fill out your copyright notice in the Description page of Project Settings.

#include "UTHUB_ASC.h"

#include "NativeGameplayTags.h"

// Sets default values for this component's properties
UUTHUB_ASC::UUTHUB_ASC()
{
	// Set this component to be initialized when the game starts, and to be ticked
	// every frame.  You can turn these features off to improve performance if you
	// don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UUTHUB_ASC::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo(GetOwner(), GetOwner());
}

void UUTHUB_ASC::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	// INIT EFFECT
	// INI ATTRIBS
	// INIT SKILLS
}

// Called every frame
void UUTHUB_ASC::TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
