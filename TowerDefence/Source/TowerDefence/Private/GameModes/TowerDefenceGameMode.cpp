// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "TowerDefenceGameMode.h"
#include "TowerDefence.h"
#include "PlayerCamera.h"
#include "TimerManager.h"

ATowerDefenceGameMode::ATowerDefenceGameMode() 
    :CurrentWave(0), SecondsBeforeStartWave(0)
{
    GameStateClass = ATowerDefenceGameState::StaticClass();

    DefaultPawnClass = APlayerCamera::StaticClass();

    WavesTimeSeconds.Add(5);
    WavesTimeSeconds.Add(10);
    WavesTimeSeconds.Add(15);
}

void ATowerDefenceGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    if (SecondsBeforeStartWave == 0)
    {
        SecondsBeforeStartWave = 1;
    }

    GetWorldTimerManager().SetTimer(WaveTimer, this, &ATowerDefenceGameMode::StartNextWave, SecondsBeforeStartWave);
}

void ATowerDefenceGameMode::StartNextWave()
{
    CurrentWave++;

    if(WavesTimeSeconds.Num() > 0 && WavesTimeSeconds.IsValidIndex(CurrentWave - 1))
    {
        auto WaveDuration = WavesTimeSeconds[CurrentWave - 1];
        if (WaveDuration == 0)
        {
            WaveDuration = 1;
        }

        OnWaveBegin.Broadcast(CurrentWave);
        GetWorldTimerManager().SetTimer(WaveTimer, this, &ATowerDefenceGameMode::StartNextWave, WaveDuration);
    }
}