// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "TowerDefenceGameState.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveBegin, uint8, WaveNumber);

UCLASS()
class TOWERDEFENCE_API ATowerDefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ATowerDefenceGameMode();

	UPROPERTY(BlueprintAssignable)
	FOnWaveBegin OnWaveBegin;

	UPROPERTY(BLueprintReadOnly, EditDefaultsOnly)
	TArray<uint8> WavesTimeSeconds;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    uint8 SecondsBeforeStartWave;

private:
    FTimerHandle WaveTimer;
    
    uint8 CurrentWave;

    void StartNextWave();

protected:
    void BeginPlay() override;
};
