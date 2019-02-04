// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "WaveSpawner.h"
#include "TowerDefence.h"
#include "Moveable.h"
#include "TowerDefenceGameMode.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

AWaveSpawner::AWaveSpawner(): 
    Super()
{
    const auto DefaultSize = FVector(200, 200, 200);

    AvailableArea = CreateDefaultSubobject<UBoxComponent>("AvailableArea");
    AvailableArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    AvailableArea->SetBoxExtent(DefaultSize);

    RootComponent = AvailableArea;

    Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
    Decal->SetRelativeLocation(FVector(0, 0, -DefaultSize.Z / 2));
    Decal->SetRelativeRotation(FRotator(90, 0, 0));
    Decal->AttachToComponent(AvailableArea, FAttachmentTransformRules::KeepRelativeTransform);
    Decal->DecalSize = DefaultSize;

    static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalFinder(TEXT("/Game/TowerDefence/Environment/MI_SpawnZone"));
    auto MaterialInstance = UMaterialInstanceDynamic::Create(DecalFinder.Object, NULL);
    Decal->SetDecalMaterial(MaterialInstance);
}

void AWaveSpawner::BeginPlay()
{
    World = GetWorld();
    check(World)

    TimerManager = &World->GetTimerManager();
    
    if(!Destionation)
    {
        UE_LOG(LogGame, Log, TEXT("AWaveSpawner:BeginPlay Destionation is empty"));

        return;
    }
    
    auto GameMode = World->GetAuthGameMode();

    if (GameMode)
    {
        auto TDGameMode = Cast<ATowerDefenceGameMode>(GameMode);
        if (TDGameMode)
        {
            TDGameMode->OnWaveBegin.AddDynamic(this, &AWaveSpawner::SpawnWave);
        }
    }

    Super::BeginPlay();
}

FVector AWaveSpawner::GetRandomLocationInAvailableArea(bool bIsAir) const
{
    const FVector Origin = AvailableArea->Bounds.Origin,
        Extent = AvailableArea->Bounds.BoxExtent,
        BoxMin = Origin - Extent,
        BoxMax = Origin + Extent;
    auto Location = FMath::RandPointInBox(FBox(BoxMin, BoxMax));

    if (!bIsAir)
    {
        Location.Z = GetActorLocation().Z;
    }

    if (Location.Z < 100)
    {
        Location.Z = 100;
    }

    return Location;
}

void AWaveSpawner::SpawnWave(uint8 WaveNumber)
{
    if (WaveSettings.Contains(WaveNumber))
    {
        const FWaveSetting& Setting = WaveSettings[WaveNumber];

        if (Setting.EnemiesGroups.Num() > 0)
        {
            SpawnGroups(Setting);
        }
        else
        {
            UE_LOG(LogGame, Log, TEXT("AWaveSpawner::SpawnWave invalid setting for %s wave"), *FString::FromInt(WaveNumber));
        }
    }
}

void AWaveSpawner::SpawnActor(TSubclassOf<AActor> Type, const FRotator& Rotation)
{
    auto Actor = World->SpawnActor<AActor>(Type,
        GetRandomLocationInAvailableArea(false), Rotation);

    if (Actor)
    {
        auto MoveableActor = Cast<IMoveable>(Actor);

        if (MoveableActor)
        {
            MoveableActor->MoveToActor(Destionation);
            BP_OnActorSpawn(Actor);
        }
    }
}

void AWaveSpawner::SpawnGroup(const FWaveGroupSetting& Setting, const FRotator& Rotation)
{
    for (auto enemyNumber = 0; enemyNumber < Setting.GroupCount; enemyNumber++)
    {
        SpawnActor(Setting.GroupType, Rotation);
    }
}

void AWaveSpawner::SpawnGroups(const FWaveSetting& Setting)
{
    const auto Rotation = GetActorRotation();
    float DeltaSeconds = 0.1;

    for (auto groupNumber = 0; groupNumber < Setting.EnemiesGroups.Num(); groupNumber++)
    {
        const FWaveGroupSetting& GroupSetting = Setting.EnemiesGroups[groupNumber];

        for (auto repeatCount = 0; repeatCount <= GroupSetting.RepeatCount; repeatCount++)
        {
            FTimerDelegate TimerDelegate;
            FTimerHandle TimerHandle;
            TimerDelegate.BindUFunction(this, FName("SpawnGroup"), GroupSetting, Rotation);

            TimerManager->SetTimer(TimerHandle, TimerDelegate, DeltaSeconds, false);

            DeltaSeconds += Setting.EnemiesGroups[groupNumber].DelayTime;
        }
    }
}
