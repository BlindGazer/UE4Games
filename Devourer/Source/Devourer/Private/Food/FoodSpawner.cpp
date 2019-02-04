// Copyright 2018 GitHub BlindGazer, All Rights Reserved..

#include "FoodSpawner.h"
#include "Food.h"
#include "Components/BoxComponent.h"

AFoodSpawner::AFoodSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    SpawningVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningVolume"));
    ToFoodSpawn = AFood::StaticClass();
    RootComponent = SpawningVolume;
}

FVector AFoodSpawner::GetRandomPointInVolume()
{
    const FVector Origin = SpawningVolume->Bounds.Origin,
        Extent = SpawningVolume->Bounds.BoxExtent,
        BoxMin = Origin - Extent,
        BoxMax = Origin + Extent;

    return FMath::RandPointInBox(FBox(BoxMin, BoxMax));
}

AFood* AFoodSpawner::Spawn()
{
    if (ToFoodSpawn)
    {
        UWorld* World = GetWorld();

        if (World)
        {
            const FVector& Location = GetRandomPointInVolume();
            auto Food = World->SpawnActor<AFood>(ToFoodSpawn, Location, FRotator::ZeroRotator);
            Food->OnDestroyed.AddDynamic(this, &AFoodSpawner::DestroyedFood);

            return Food;
        }
    }

    return nullptr;
}

void AFoodSpawner::DestroyedFood(AActor* Food)
{
    Spawn();
}

void AFoodSpawner::BeginPlay()
{
    Super::BeginPlay();

    Spawn();
}